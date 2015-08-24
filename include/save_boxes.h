#ifndef SAVE_BOXES_H
#define SAVE_BOXES_H

#include <inttypes.h>

#include "save_common.h"
#include "save_pokemon.h"

#define SAVE_PARTY_SLOTS 6

#define SAVE_BOXES 14
#define SAVE_BOX_SLOTS 30
#define SAVE_BOX_NAME_LENGTH 9

struct save_box_data_t {
    uint32_t current;
    struct save_pokemon_boxed_t pokemon[SAVE_BOXES][SAVE_BOX_SLOTS];
    uint8_t names[SAVE_BOXES][SAVE_BOX_NAME_LENGTH];
    uint8_t wallpapers[SAVE_BOXES];
};

struct save_box_unpacked_t {
    struct save_pokemon_boxed_t pokemon[SAVE_BOX_SLOTS];
    char name[SAVE_BOX_NAME_LENGTH];
    uint8_t wallpaper;
};

#endif
