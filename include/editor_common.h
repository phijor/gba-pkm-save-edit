#ifndef  EDITOR_COMMON_H
#define  EDITOR_COMMON_H

union save_unpacked_t;

struct editor_command_t {
    const char* name;
    int (*exec)(union save_unpacked_t* save, int argc, char* const* argv);
};

void editor_print_commands(const struct editor_command_t commands[]);

void editor_error_unknown_command(const struct editor_command_t commands[],
                                  const char unknown[]);

#endif   /* ----- #ifndef EDITOR_COMMON_H  ----- */
