#ifndef EDITOR_DUMP_H
#define EDITOR_DUMP_H

union save_unpacked_t;

int editor_dump(union save_unpacked_t* save, int argc, char* const* argv);

#endif
