#include <sys/types.h>

#include "editor_common.h"
#include "message.h"

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

