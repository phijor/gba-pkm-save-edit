#ifndef  MESSAGE_H
#define  MESSAGE_H

#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MSG_COLOR_INFO ANSI_COLOR_GREEN
#define MSG_COLOR_WARNING ANSI_COLOR_YELLOW
#define MSG_COLOR_ERROR ANSI_COLOR_RED
#define MSG_COLOR_PROMPT ANSI_COLOR_CYAN
#define MSG_COLOR_INTERNAL ANSI_COLOR_BLUE
#define MSG_COLOR_BULLET ANSI_COLOR_GREEN

#define MSG_RESET ANSI_COLOR_RESET

#define MSG_SPACES_PER_INDENT 4

enum message_type_t {
    MSG_NORMAL,
    MSG_INFO,
    MSG_WARNING,
    MSG_ERROR,
    MSG_PROMPT,
    MSG_BULLET,
};

struct message_format_t {
    enum message_type_t type;
    int indent;
};

void message_init(FILE* output, FILE* error, FILE* input);
void message_set_output(FILE* output);
void message_set_error(FILE* error);

int message_indent(int ammount);
int message(const char* const format, const char* const message, ...);
void message_read_line(char* string, size_t length);

#endif
