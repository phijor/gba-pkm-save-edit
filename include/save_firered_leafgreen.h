#ifndef SAVE_FIRERED_LEAFGREEN_H
#define SAVE_FIRERED_LEAFGREEN_H

#include <inttypes.h>

#include "save_common.h"

struct save_firered_leafgreen_t {
    //uint8_t data[55552];

    struct save_trainer_info_t player;
    uint8_t _0[8];

    uint8_t pokedex_national_unlocked_A;
    uint8_t _1[13];

    uint8_t pokedex_owned[SAVE_DEX_BYTE_SIZE];
    uint8_t _2[3];

    uint8_t pokedex_seen_a[SAVE_DEX_BYTE_SIZE];
    uint8_t _3[31];

    uint32_t game_code;
};

#endif
