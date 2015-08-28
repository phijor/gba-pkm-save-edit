#ifndef  SAVE_POKEMON_STORAGE_H
#define  SAVE_POKEMON_STORAGE_H

#include "save_pokemon.h"
#include "save_boxes.h"

#define SAVE_PARTY_SLOTS 6

union save_unpacked_t;
struct save_box_unpacked_t;

int save_pokemon_get_party(union save_unpacked_t* save,
                          struct save_pokemon_boxed_t* party);

int save_pokemon_get_box(union save_unpacked_t* save, size_t index,
                         struct save_box_unpacked_t* box);

uint32_t save_pokemon_get_party_size(union save_unpacked_t* save);

int save_pokemon_slot_is_empty(struct save_pokemon_boxed_t* pokemon);

#endif   /* ----- #ifndef SAVE_POKEMON_STORAGE_H----- */
