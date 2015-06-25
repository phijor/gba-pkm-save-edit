#ifndef EDITOR_SHOW_H
#define EDITOR_SHOW_H

union save_unpacked_t;

int editor_show(union save_unpacked_t* save, int argc, char* const* argv);
int editor_show_pokedex(union save_unpacked_t* save, int argc, char* const* argv);

#endif
