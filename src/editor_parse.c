#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "editor_parse.h"

const struct editor_call_t* editor_parse_call(
    const struct editor_call_t calls[], const char parameter[]) {
    assert(calls != NULL && parameter != NULL);
    for (size_t i = 0; calls[i].name != NULL; i++) {
        assert(calls[i].exec != NULL);
        if (strcmp(calls[i].name, parameter) == 0) {
            return &calls[i];
        }
    }
    editor_error_unknown_call(calls, parameter);
    return NULL;
}

int editor_parse_range(struct editor_range_t* range, const char parameter[]) {
    assert(parameter != NULL);
    // if `parameter` starts with '-', set the lower bound to the lowest value
    // possible.
    if (parameter[0] == '-') {
        range->lower = range->min;
    }
    // if `parameter` starts with a number, parse it and set it as lower bound.
    else if (isdigit(parameter[0])) {
        range->lower = atoi(parameter);
    }
    // otherwise, fail because there's no valid lower bound to be extracted.
    else {
        return EXIT_FAILURE;
    }

    // interate through the number that `parameter` starts with
    char* index = (char*)parameter;
    for (; isdigit(index[0]); index++)
        ;

    // if the string ends after the first number, assume the range to only span
    // one value.
    if (index[0] == '\0'){
        range->upper = range->lower;
    }
    // if the next character is '-', point to the following one and...
    else if (*(index++) == '-') {
        // ...parse it, if it's a number...
        if (isdigit(index[0])) {
            range->upper = atoi(index);
        }
        // ...or set the upper bound to the maximum value, if the string ends
        // there...
        else if (index[0] == '\0'){
            range->upper = range->max;
        }
        // ...or fail if there's any other character.
        else {
            return EXIT_FAILURE;
        }
    }
    // otherwise, fail because there's invalid characters following.
    else {
        return EXIT_FAILURE;
    }

    if (range->lower < range->min) {
        range->lower = range->min;
    }
    if (range->upper > range->max) {
        range->upper = range->max;
    }
    return EXIT_SUCCESS;
}
