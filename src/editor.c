#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>

#include "message.h"
#include "editor.h"
#include "editor_parse.h"
#include "editor_show.h"
#include "editor_dump.h"
#include "editor_export.h"

#include "save.h"
#include "save_integrity.h"
#include "save_unpacked.h"

#define ARG_MAX_STR_LEN 80
#define ARG_SEPERATOR " \t\n\r"

int editor(struct editor_options_t* options,int argc, char* const* argv) {
    if (argc < 1 || options->h_show_help) {
        editor_print_usage(options->progname);
        return EXIT_SUCCESS;
    }

    FILE* save_file;
    if (options->i_input_file == NULL) {
        message("W", "No input file specified.\n");
        options->i_input_file = "stdin";
        save_file = stdin;
    } else {
        save_file = fopen(options->i_input_file, "r");
    }
    message("I", "Reading from \'%s\'.\n", options->i_input_file);
    if (save_file == NULL) {
        message("E", "Unable to open '%s'.\n", options->i_input_file);
        return EXIT_FAILURE;
    }

    struct save_file_t save;
    fread(&save, sizeof(save), 1, save_file);
    fclose(save_file);

    if (save_file_integrity_check(&save) == EXIT_FAILURE) {
        message("E", "Save file seems to be corrupt.\n");
        return EXIT_FAILURE;
    }
    message("I", "Save file passed integrity-test.\n");

    struct save_block_t* most_recent;
    save_block_recent_get(&save, &most_recent);
    union save_unpacked_t unpacked;
    save_unpack(most_recent, &unpacked);

    const struct editor_call_t calls[] = {
        {.name = "show", .exec = &editor_show},
        {.name = "dump", .exec = &editor_dump},
        {.name = "export", .exec = &editor_export},
        {.name = NULL, .exec = NULL},
    };
    int exit_status = editor_call(&unpacked, calls, argc, argv);

    if (options->o_output_file != NULL) {
        editor_write_to_file(&save, &unpacked, options->o_output_file);
    }
    return exit_status;
}

int editor_call(union save_unpacked_t* save,
                const struct editor_call_t commands[], int argc,
                char* const* argv) {
    const struct editor_call_t* matched_call = NULL;
    struct editor_arguments_t arguments = {
        .input_line = NULL,
    };

    int was_interactive = 0;

    if (argc > 0) {
        //We're not going to modify argv or its contents, promised.
        arguments.vector = (char**) argv;
        arguments.count = argc;
        arguments.input_line = NULL;
    }
    else {
        was_interactive = 1;
        arguments.input_length = ARG_MAX_STR_LEN;
        editor_interactive(commands, &arguments);
    }

    matched_call = editor_parse_call(commands, arguments.vector[0]);
    if (matched_call == NULL) {
        return EXIT_FAILURE;
    }

    int exit_status =
        matched_call->exec(save, arguments.count - 1, &(arguments.vector[1]));

    if (was_interactive) {
        editor_free_args(&arguments);
    }
    return exit_status;
}

int editor_interactive(const struct editor_call_t calls[],
                       struct editor_arguments_t* arguments) {
    if (arguments->input_line != NULL) {
        editor_free_args(arguments);
    }
    arguments->input_line = malloc(arguments->input_length * sizeof(char));
    message_read_line(arguments->input_line, arguments->input_length);

    editor_count_args(arguments, ARG_SEPERATOR);

    arguments->vector = malloc(arguments->count * sizeof(char*));
    editor_get_args(arguments);
    return arguments->count;
}

int editor_write_to_file(struct save_file_t* save,
                         union save_unpacked_t* unpacked, char* file_name) {
    message("I", "Repacking savefile.\n");
    struct save_block_t* target_block;
    save_block_old_get(save, &target_block);
    int repack_status =
        save_repack(target_block, unpacked,
                    target_block->sections[0].signature.save_index + 1,
                    save_section_offset_get(target_block));
    if (repack_status == EXIT_FAILURE) {
        message("E", "Could not repack savefile.\n");
    }

    FILE* edited_save_file = fopen(file_name, "w");
    if (edited_save_file == NULL) {
        message("E", "Unable to open '%s'\n", file_name);
        return EXIT_FAILURE;
    }
    message("I", "Writing edited savefile to '%s'\n", file_name);
    fwrite(&save, sizeof(save), 1, edited_save_file);
    return EXIT_SUCCESS;
}

int editor_get_args(struct editor_arguments_t* args) {
    const char* seperator = ARG_SEPERATOR;
    args->vector[0] = strtok(args->input_line, seperator);

    ssize_t i;
    for (i = 1; i < args->count; i++) {
        char* current_arg = strtok(NULL, seperator);
        if (current_arg == NULL) {
            break;
        }
        args->vector[i] = current_arg;
    }
    return args->count = i;
}

void editor_free_args(struct editor_arguments_t* args) {
    free((void*) args->vector);
    free((void*) args->input_line);
}

int editor_count_args(struct editor_arguments_t* args, char* seperator) {
    if (args->input_line[0] == '\0') {
        return args->count = 0;
    }
    int count = 1;
    int was_sep = 0;
    for (size_t i = 0; args->input_line[i] != '\0'; i++) {
        int is_sep = 0;
        for (size_t j = 0; seperator[j] != '\0'; j++) {
            if (args->input_line[i] == seperator[j]) {
                is_sep = 1;
                break;
            }
        }
        if (is_sep && !was_sep) {
            count++;
        }
        was_sep = is_sep;
    }
    return args->count = count;
}
