#ifndef EDITOR_H
#define EDITOR_H

#include <stddef.h>

union save_unpacked_t;

struct editor_command_t {
    const char* name;
    int (*exec)(union save_unpacked_t* save, int argc, char* const* argv);
};

struct editor_arguments_t {
        int count;
        char** vector;
        char* input_line;
        size_t input_length;
};

int editor(union save_unpacked_t* save, int argc, char* const* argv);

int editor_call(union save_unpacked_t* save,
                const struct editor_command_t commands[], int argc,
                char* const* argv);

const struct editor_command_t* editor_parse(
    const struct editor_command_t commands[], const char parameter[]);

int editor_interactive(const struct editor_command_t commands[],
                       struct editor_arguments_t* arguments);

void editor_print_commands(const struct editor_command_t commands[]);

void editor_error_unknown_command(const struct editor_command_t commands[],
                                  const char unknown[]);

int editor_dump(union save_unpacked_t* save, int argc, char* const* argv);

int editor_get_args(struct editor_arguments_t* args);

int editor_count_args(struct editor_arguments_t*, char* seperator);

void editor_free_args(char** argv, int argc);

#endif
