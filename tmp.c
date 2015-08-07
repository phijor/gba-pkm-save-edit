#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "message.h"
#include "editor.h"
#include "editor_show.h"
#include "editor_dump.h"

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
    char** editor_argv;
    int editor_argc;

    int was_interactive = 0;

    if (argc > 0) {
        editor_argv = (char**) argv; //We're not going to modify argv or its
                                     //contents, promised.
        editor_argc = argc;
    }
    else {
        was_interactive = 1;
        static const size_t arg_depth = 10;
        editor_argv = malloc(arg_depth * sizeof(editor_argv[0]));
        editor_argc = editor_interactive(commands, editor_argv, arg_depth);
    }

    matched_command = editor_parse(commands, editor_argv[0]);
    if (matched_command == NULL) {
        return EXIT_FAILURE;
    }

    int exit_status =
        matched_command->exec(save, editor_argc - 1, &(editor_argv[1]));

    if (was_interactive) {
        free((void*) editor_argv);
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

int editor_interactive(const struct editor_command_t commands[], char** argv,
                       size_t arg_depth) {
    message("I+", "Available commands:\n");
    editor_print_commands(commands);

    return message_read_args(argv, arg_depth);
}

void editor_print_commands(const struct editor_command_t commands[]) {
    for (size_t i = 0; commands[i].name != NULL; i++) {
        message("", "%s\n", commands[i].name);
    }
}
void editor_error_unknown_command(const struct editor_command_t commands[],
                                  const char unknown[]) {
    message("E", "Unknown command \"%s\". Valid commands are:\n", unknown);
    editor_print_commands(commands);
}
