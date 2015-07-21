#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "message.h"

FILE* message_output;
FILE* message_error;
int message_indent_level = {0};

void message_set_output(FILE* output) {
    assert(output != NULL);
    message_output = output;
}

void message_set_error(FILE* error) {
    assert(error != NULL);
    message_error = error;
}

void message_init(FILE* output, FILE* error) {
    message_set_output(output);
    message_set_error(error);
}

int message_indent(int ammount) {
    return message_indent_level += ammount;
}

int message_parse_format(const char* const format_string, struct message_format* format) {
    for (size_t i = 0; format_string[i] != '\0'; i++) {
        switch (format_string[i]) {
            case '+':
                format->indent++;
                break;
            case '-':
                format->indent--;
                break;
            case 'I':
                format->type = MSG_INFO;
                break;
            case 'W':
                format->type = MSG_WARNING;
                break;
            case 'E':
                format->type = MSG_ERROR;
                break;
        }
    }
    return EXIT_SUCCESS;
}

int message(const char* const format_string, const char* const message) {
    if (message_output == NULL) {
        message_set_output(stdout);
    }
    if (message_error == NULL) {
        message_set_error(stderr);
    }

    struct message_format format = {
        .type = MSG_NORMAL,
        .indent = 0,
    };
    message_parse_format(format_string, &format);

    const char* prefixes[] = {
            [MSG_NORMAL] = "",
            [MSG_INFO] =    MSG_COLOR_INFO    "[INFORMATION]: " MSG_RESET,
            [MSG_WARNING] = MSG_COLOR_WARNING "[WARNING]: " MSG_RESET,
            [MSG_ERROR] =   MSG_COLOR_ERROR   "[ERROR]: " MSG_RESET,
    };

    FILE* current_output = NULL;
    switch (format.type) {
        case MSG_NORMAL:
        case MSG_INFO:
        case MSG_WARNING:
            current_output = message_output;
            break;
        case MSG_ERROR:
            current_output = message_error;
            break;
        default:
            fprintf(message_output, MSG_COLOR_INTERNAL "Invalid type of message specified.\n");
            return EXIT_FAILURE;
    }

    fprintf(current_output, "%*s%s%s\n",
            message_indent_level * MSG_SPACES_PER_INDENT, "", prefixes[format.type],
            message);

    message_indent(format.indent);
    return EXIT_SUCCESS;
}
