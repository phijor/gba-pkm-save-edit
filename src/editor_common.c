#include <sys/types.h>

#include "editor_common.h"
#include "message.h"

void editor_print_calls(const struct editor_call_t calls[]) {
    for (size_t i = 0; calls[i].name != NULL; i++) {
        message("*", "%s\n", calls[i].name);
    }
}

void editor_print_usage(char* progname) {
    message("0", "Usage: %s [options] commands...\n", progname);
    message("",
            "\n"
            "Options:\n"
            "-h            --  This help text.\n"
            "-i <savefile> --  The savefile to read from. Default: stdin\n"
    );
}

void editor_error_unknown_call(const struct editor_call_t commands[],
                                  const char unknown[]) {
    message("E", "Unknown command \"%s\". Valid commands are:\n", unknown);
    editor_print_calls(commands);
}
