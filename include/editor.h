#ifndef EDITOR_H
#define EDITOR_H

#include <stddef.h>

#include "editor_common.h"

union save_unpacked_t;
struct save_file_t;

struct editor_arguments_t {
        int count;
        char** vector;
        char* input_line;
        size_t input_length;
};

struct editor_options_t {
    char* o_output_file;
    char* i_input_file;
    char* progname;
    int h_show_help;
};

int editor(struct editor_options_t* options, int argc, char* const* argv);

int editor_call(union save_unpacked_t* save,
                const struct editor_call_t commands[], int argc,
                char* const* argv);

int editor_interactive(const struct editor_call_t calls[],
                       struct editor_arguments_t* arguments);

int editor_dump(union save_unpacked_t* save, int argc, char* const* argv);

int editor_write_to_file(struct save_file_t* save,
                         union save_unpacked_t* unpacked, char* file_name);

int editor_get_args(struct editor_arguments_t* args);

int editor_count_args(struct editor_arguments_t*, char* seperator);

void editor_free_args(struct editor_arguments_t* args);

#endif
