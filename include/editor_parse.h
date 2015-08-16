#ifndef  EDITOR_PARSE_H
#define  EDITOR_PARSE_H

#include "editor_common.h"

//const struct editor_command_t* editor_parse(
//    const struct editor_command_t commands[], const char parameter[]);

const struct editor_call_t* editor_parse_call(
    const struct editor_call_t commands[], const char parameter[]);

int editor_parse_range(struct editor_range_t* range, const char parameter[]);

#endif   /* ----- #ifndef EDITOR_PARSE_H  ----- */
