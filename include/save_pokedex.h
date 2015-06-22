#ifndef SAVE_POKEDEX_H
#define SAVE_POKEDEX_H

#include <inttypes.h>

//#include "save_unpacked.h"
#include "save_pokedex_types.h"

union save_unpacked_t;
struct save_pokedex_t;

int save_pokedex_search(struct save_pokedex_t* pokedex, uint16_t index);

enum save_pokedex_status_t save_get_pokedex_entry(
    union save_unpacked_t* save, uint16_t index);

void save_pokedex_basic_set(struct save_pokedex_t* pokedex, uint16_t index);
void save_pokedex_clear_entry(struct save_pokedex_t* pokedex, uint16_t index);
int save_set_pokedex_entry(union save_unpacked_t* save, uint16_t index,
                           enum save_pokedex_status_t status);
#endif
