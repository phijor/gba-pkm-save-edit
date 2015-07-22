#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

#include "message.h"

FILE* message_output;
FILE* message_error;
FILE* message_input;

int message_indent_level = {0};

void message_set_output(FILE* output) {
    assert(output != NULL);
    message_output = output;
}

void message_set_error(FILE* error) {
    assert(error != NULL);
    message_error = error;
}

void message_set_input(FILE* input) {
    assert(input != NULL);
    message_input = input;
}

void message_init(FILE* output, FILE* error, FILE* input) {
    message_set_output(output);
    message_set_error(error);
    message_set_input(input);
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
            case 'P':
                format->type = MSG_PROMPT;
                break;
        }
    }
    return EXIT_SUCCESS;
}

int message(const char* const format_string, const char* const message, ...) {
    va_list args;
    va_start(args, message);

    if (message_output == NULL) {
        message_set_output(stdout);
    }
    if (message_error == NULL) {
        message_set_error(stderr);
    }
    if (message_input == NULL) {
        message_set_input(stdin);
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
            [MSG_PROMPT] =   MSG_COLOR_PROMPT   "[>]: " MSG_RESET,
    };

    FILE* current_output = NULL;
    switch (format.type) {
        case MSG_NORMAL:
        case MSG_INFO:
        case MSG_WARNING:
        case MSG_PROMPT:
            current_output = message_output;
            break;
        case MSG_ERROR:
            current_output = message_error;
            break;
        default:
            fprintf(message_output, MSG_COLOR_INTERNAL "Invalid type of message specified.\n");
            return EXIT_FAILURE;
    }

    fprintf(current_output, "%*s%s",
            message_indent_level * MSG_SPACES_PER_INDENT, "", prefixes[format.type]);
    vfprintf(current_output, message, args);
    va_end(args);

    message_indent(format.indent);
    return EXIT_SUCCESS;
}

void message_read_line(char* string, size_t length) {
    message("P", "");
    fgets(string, length, stdin);
    string[strcspn(string, "\r\n")] = '\0';
}
