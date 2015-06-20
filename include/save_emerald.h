#ifndef SAVE_EMERALD_H
#define SAVE_EMERALD_H

#include <inttypes.h>

#include "save_common.h"

struct save_emerald_t {
    //uint8_t data[55552];

    struct save_trainer_info_t player;
    uint8_t _0[6];

    uint16_t pokedex_national_unlocked_A;
    uint8_t _1[14];

    uint8_t pokedex_owned[SAVE_DEX_BYTE_SIZE];
    uint8_t _2[3];

    uint8_t pokedex_seen_a[SAVE_DEX_BYTE_SIZE];
    uint8_t _3[31];

    uint32_t security_key;
};

#endif
