#ifndef  SAVE_POKEMON_STORAGE_H
#define  SAVE_POKEMON_STORAGE_H

#include <inttypes.h>
#include <stddef.h>

#define SAVE_PARTY_SLOTS 6

union save_unpacked_t;
struct save_box_unpacked_t;
struct save_pokemon_t;

enum save_storage_occupancy_t {
    SAVE_STORAGE_EMPTY,
    SAVE_STORAGE_EGG,
    SAVE_STORAGE_POKEMON,
};

int save_storage_party_get(union save_unpacked_t* save,
                          struct save_pokemon_t* party);

int save_storage_box_get(union save_unpacked_t* save, size_t index,
                         struct save_box_unpacked_t* box);

uint32_t save_storage_party_size_get(union save_unpacked_t* save);

int save_storage_slot_is_empty(struct save_pokemon_t* pokemon);

int save_storage_slot_is_egg(struct save_pokemon_t* pokemon);

#endif   /* ----- #ifndef SAVE_POKEMON_STORAGE_H----- */
