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
    if (argc > 0) {
        matched_command = editor_parse(commands, argv[0]);
    }
    else {
        matched_command = editor_interactive(commands);
    }
    if (matched_command == NULL) {
        return EXIT_FAILURE;
    }
    return matched_command->exec(save, argc - 1, &(argv[1]));
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

const struct editor_command_t* editor_interactive(const struct editor_command_t commands[]) {
#define INPUT_MAX_LENGTH 80
    char input_string[INPUT_MAX_LENGTH];
    message("I+", "Available commands:\n");
    editor_print_commands(commands);

    message_read_line(input_string, sizeof(input_string));
    return editor_parse(commands, input_string);
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
