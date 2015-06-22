#ifndef SAVE_BOXES_H
#define SAVE_BOXES_H

#include <inttypes.h>

#include "save_pokemon.h"

#define SAVE_BOXES 14

struct save_box_data_t {
    uint32_t current;
    struct save_boxed_pokemon_t pokemon[SAVE_BOXES][30];
    uint8_t names[SAVE_BOXES][9];
    uint8_t wallpapers[SAVE_BOXES];
};

#endif
