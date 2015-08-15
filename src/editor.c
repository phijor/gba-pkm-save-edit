#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

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
    arguments->count = message_get_args(arguments->input_line, arguments->vector, arg_depth);
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

void editor_free_args(char** argv, int argc) {
    free((void*) argv[0]);
    free((void*)argv);
}
