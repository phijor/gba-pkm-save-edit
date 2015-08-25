#ifndef SAVE_FIRERED_LEAFGREEN_H
#define SAVE_FIRERED_LEAFGREEN_H

#include <inttypes.h>

#include "save_common.h"
#include "save_pokedex.h"
#include "save_pokemon.h"
#include "save_boxes.h"

struct __attribute__((packed)) save_firered_leafgreen_items_t {
    struct save_item_t pc_storage[30];
    struct save_item_t item_pocket[42];
    struct save_item_t key_item_pocket[30];
    struct save_item_t ball_pocket[13];
    struct save_item_t tm_case[58];
    struct save_item_t berry_pouch[43];
};

struct save_firered_leafgreen_t {
    struct save_trainer_info_t player;
    //buffer:  (next - previous) - previous_size
    uint8_t _0[(0x001b - 0x0000) - sizeof(struct save_trainer_info_t)];

    uint8_t pokedex_national_unlocked_a;
    uint8_t _1[(0x0028 - 0x001b) - sizeof(uint8_t)];

    struct save_pokedex_t pokedex_owned;
    uint8_t _2[(0x005c - 0x0028) - sizeof(struct save_pokedex_t)];

    struct save_pokedex_t pokedex_seen_a;
    uint8_t _3[(0x00ac - 0x005c) - sizeof(struct save_pokedex_t)];

    uint32_t game_code;
    uint8_t _4[(0x0af8 - 0x00ac) - sizeof(uint32_t)];

    uint32_t security_key;
    uint8_t _5[(0x0f60 - 0x0af8) - sizeof(uint32_t)];

    uint32_t party_size;
    struct save_pokemon_t party[6];
    uint32_t money;
    uint16_t coins;
    uint8_t _6[(0x11c4 - 0x0f60) - 2 * sizeof(uint32_t) -
               sizeof(uint16_t) - 6*sizeof(struct save_pokemon_t)];

    struct save_firered_leafgreen_items_t items;
    uint8_t _7[(0x1524 - 0x11c4) - sizeof(struct save_firered_leafgreen_items_t)];

    struct save_pokedex_t pokedex_seen_b;
    uint8_t _8[(0x1f14 - 0x1524) - sizeof(struct save_pokedex_t)];

    uint8_t pokedex_national_unlocked_b;
    uint8_t _9[(0x1fc8 - 0x1f14) - sizeof(uint8_t)];

    uint16_t pokedex_national_unlocked_c;
    uint8_t _10[(0x4944 - 0x1fc8) - sizeof(uint16_t)];

    struct save_pokedex_t pokedex_seen_c;
    uint8_t _11[(0x4978 - 0x4944) - sizeof(struct save_pokedex_t)];

    uint8_t rival_name[8];
    uint8_t _12[(0x4cb4 - 0x4978) - 8*sizeof(uint8_t)];

    struct save_box_data_t boxes;
};

#endif
