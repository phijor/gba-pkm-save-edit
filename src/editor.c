#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>

#include "message.h"
#include "editor.h"
#include "editor_show.h"
#include "editor_dump.h"

#define ARG_MAX_STR_LEN 80
#define	ARG_MAX_DEPTH 5

int editor(union save_unpacked_t* save, int argc, char* const* argv) {
    const struct editor_command_t commands[] = {
        {.name = "show", .exec = &editor_show},
        {.name = "dump", .exec = &editor_dump},
        {.name = NULL, .exec = NULL},
    };
    return editor_call(save, commands, argc, argv);
}

int editor_call(union save_unpacked_t* save,
                const struct editor_command_t commands[], int argc,
                char* const* argv) {
    const struct editor_command_t* matched_command;
    struct editor_arguments_t arguments;

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
        editor_interactive(commands, &arguments, ARG_MAX_DEPTH);
    }

    matched_command = editor_parse(commands, arguments.vector[0]);
    if (matched_command == NULL) {
        return EXIT_FAILURE;
    }

    int exit_status =
        matched_command->exec(save, arguments.count - 1, &(arguments.vector[1]));

    if (was_interactive) {
        free(arguments.vector);
        free(arguments.input_line);
    }
    return exit_status;
}

const struct editor_command_t* editor_parse(
    const struct editor_command_t commands[], const char parameter[]) {
    assert(commands != NULL && parameter != NULL);
    for (size_t i = 0; commands[i].exec != NULL; i++) {
        assert(commands[i].name != NULL);
        if (strcmp(commands[i].name, parameter) == 0) {
            return &commands[i];
        }
    }
    editor_error_unknown_command(commands, parameter);
    return NULL;
}

int editor_interactive(const struct editor_command_t commands[],
                       struct editor_arguments_t* arguments, size_t arg_depth) {
    message("", "Commands available:\n");
    editor_print_commands(commands);

    arguments->input_line = malloc(arguments->input_length * sizeof(char));
    arguments->vector = malloc(arg_depth * sizeof(char*));

    message_read_line(arguments->input_line, arguments->input_length);

    arguments->count = arg_depth;
    editor_get_args(arguments);
    return arguments->count;
}

void editor_print_commands(const struct editor_command_t commands[]) {
    for (size_t i = 0; commands[i].name != NULL; i++) {
        message("*", "%s\n", commands[i].name);
    }
}

void editor_error_unknown_command(const struct editor_command_t commands[],
                                  const char unknown[]) {
    message("E", "Unknown command \"%s\". Valid commands are:\n", unknown);
    editor_print_commands(commands);
}

int editor_get_args(struct editor_arguments_t* args) {
    const char* seperator = " \t\n\r";
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

void editor_free_args(char** argv, int argc) {
    free((void*) argv[0]);
    free((void*)argv);
}

int editor_count_args(char* arg_string, char* seperator) {
    if (arg_string[0] == '\0') {
        return 0;
    }
    int count = 1;
    int was_sep = 0;
    for (size_t i = 0; arg_string[i] != '\0'; i++) {
        int is_sep = 0;
        for (size_t j = 0; seperator[j] != '\0'; j++) {
            if (arg_string[i] == seperator[j]) {
                is_sep = 1;
                break;
            }
        }
        if (is_sep && !was_sep) {
            count++;
        }
        was_sep = is_sep;
    }
    return count;
}
