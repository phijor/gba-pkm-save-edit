#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

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
    const struct editor_command_t* matched_command =
        editor_parse(commands, argv[0]);
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

void editor_print_commands(const struct editor_command_t commands[]) {
    for (size_t i = 0; commands[i].name != NULL; i++) {
        fprintf(stderr, "%s\n", commands[i].name);
    }
}
void editor_error_unknown_command(const struct editor_command_t commands[],
                                  const char unknown[]) {
    fprintf(stderr, "Unknown command \"%s\". Valid commands are:\n", unknown);
    editor_print_commands(commands);
}
