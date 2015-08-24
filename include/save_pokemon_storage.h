#ifndef  SAVE_POKEMON_STORAGE_H
#define  SAVE_POKEMON_STORAGE_H

#include "save_pokemon.h"

#define SAVE_PARTY_SLOTS 6
#define SAVE_BOX_SLOTS 30

union save_unpacked_t;

int save_pokemon_get_party(union save_unpacked_t* save,
                          struct save_pokemon_boxed_t* party);

uint32_t save_pokemon_get_party_size(union save_unpacked_t* save);

int save_pokemon_slot_is_empty(struct save_pokemon_boxed_t* pokemon);

#endif   /* ----- #ifndef SAVE_POKEMON_STORAGE_H----- */
