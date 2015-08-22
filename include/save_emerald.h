#ifndef SAVE_EMERALD_H
#define SAVE_EMERALD_H

#include <inttypes.h>

#include "save_common.h"
#include "save_pokedex.h"
#include "save_pokemon.h"
#include "save_boxes.h"

struct save_emerald_items_t {
    struct save_item_t pc_storage[50];
    struct save_item_t item_pocket[30];
    struct save_item_t key_item_pocket[30];
    struct save_item_t ball_pocket[16];
    struct save_item_t tm_case[64];
    struct save_item_t berry_pouch[46];
};

struct save_emerald_t {
    struct save_trainer_info_t player;
    uint8_t _0[(0x0019 - 0x0000) - sizeof(struct save_trainer_info_t)];

    uint8_t pokedex_national_unlocked_a;
    uint8_t _1[(0x0028 - 0x0019) - sizeof(uint8_t)];

    struct save_pokedex_t pokedex_owned;
    uint8_t _2[(0x005c - 0x0028) - sizeof(struct save_pokedex_t)];

    struct save_pokedex_t pokedex_seen_a;
    uint8_t _3[(0x00ac - 0x005c) - sizeof(struct save_pokedex_t)];

    uint32_t security_key;
    uint8_t _4[(0x1228 - 0x00ac) - sizeof(uint32_t)];

    uint32_t party_size;
    struct save_pokemon_t party[6];
    uint32_t money;
    uint8_t _6[(0x148c - 0x1228) - 2 * sizeof(uint32_t) -
               6*sizeof(struct save_pokemon_t)];

    struct save_emerald_items_t items;
    uint8_t _7[(0x197c - 0x148c) - sizeof(struct save_emerald_items_t)];

    struct save_pokedex_t pokedex_seen_b;
    uint8_t _8[(0x2302 - 0x197c) - sizeof(struct save_pokedex_t)];

    uint8_t pokedex_national_unlocked_b;
    uint8_t _9[(0x2490 - 0x2302) - sizeof(uint8_t)];

    uint16_t pokedex_national_unlocked_c;
    uint8_t _10[(0x4c74 - 0x2490) - sizeof(uint16_t)];

    struct save_pokedex_t pokedex_seen_c;
    uint8_t _11[(0x4fc4 - 0x4c74) - 8*sizeof(uint8_t)];

    struct save_box_data_t boxes;
    //last byte at 0xdf58
};

#endif
