#ifndef  EDITOR_PARSE_H
#define  EDITOR_PARSE_H

#include "editor_common.h"

const struct editor_command_t* editor_parse(
    const struct editor_command_t commands[], const char parameter[]);

#endif   /* ----- #ifndef EDITOR_PARSE_H  ----- */
