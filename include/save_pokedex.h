#ifndef SAVE_POKEDEX_H
#define SAVE_POKEDEX_H

#include <inttypes.h>

#define SAVE_DEX_BYTE_SIZE 49

enum save_pokedex_status_t {
    UNSEEN,
    SEEN,
    OWNED,
    POKEDEX_SUCCESS,
    POKEDEX_ERROR,
};

struct save_pokedex_t {
    uint8_t data[SAVE_DEX_BYTE_SIZE];
};

union save_unpacked_t;

enum save_pokedex_status_t save_get_pokedex_save_entry(union save_unpacked_t* save, uint16_t index);

#endif
