#ifndef  EDITOR_COMMON_H
#define  EDITOR_COMMON_H

union save_unpacked_t;

enum editor_command_type_t {
    EDITOR_NONE = 0,
    EDITOR_CALL,
    EDITOR_RANGE,
};

struct editor_range_t {
    int min;
    int max;
    int lower;
    int upper;
};

struct editor_call_t {
    const char* name;
    int (*exec)(union save_unpacked_t* save, int argc, char* const* argv);
};

void editor_print_calls(const struct editor_call_t calls[]);

void editor_error_unknown_call(const struct editor_call_t commands[],
                                  const char unknown[]);

#endif   /* ----- #ifndef EDITOR_COMMON_H  ----- */
