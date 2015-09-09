#ifndef SAVE_EMERALD_H
#define SAVE_EMERALD_H

#include <inttypes.h>

#include "save_common.h"
#include "save_pokedex.h"
#include "save_pokemon.h"
#include "save_boxes.h"
#include "save_storage.h"
#include "save_link.h"

#define SAVE_WALDAS_PHRASE_LENGTH 16

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
    uint8_t _4[(0x0eb8 - 0x00ac) - sizeof(uint32_t)];

    uint16_t battle_points;
    uint8_t _5[(0x1160 - 0x0eb8) - sizeof(uint16_t)];

    uint32_t party_size;
    struct save_pokemon_extended_t party[SAVE_PARTY_SLOTS];
    uint32_t money;
    struct save_emerald_items_t items;
    uint8_t _7[(0x18b4 - 0x1160) - 2 * sizeof(uint32_t) -
               SAVE_PARTY_SLOTS * sizeof(struct save_pokemon_extended_t) -
               sizeof(struct save_emerald_items_t)];

    struct save_pokedex_t pokedex_seen_b;
    uint8_t _8[(0x22ae - 0x18b4) - sizeof(struct save_pokedex_t)];

    uint8_t pokedex_national_unlocked_b;
    uint8_t _9[(0x2354 - 0x22ae) - sizeof(uint8_t)];

    uint16_t pokedex_national_unlocked_c;
    uint8_t _10[(0x3f5c - 0x2354) - sizeof(uint16_t)];

    struct save_pokemon_t daycare_0;
    uint8_t _12[(0x3fe8 - 0x3f5c) - sizeof(struct save_pokemon_t)];

    struct save_pokemon_t daycare_1;
    uint8_t _13[(0x407c - 0x3fe8) - sizeof(struct save_pokemon_t)];

    struct save_link_results_t link_results[SAVE_LINK_RESULTS];
    uint8_t _15[(0x4a50 - 0x407c) - sizeof(struct save_pokemon_t)];

    struct save_pokedex_t pokedex_seen_c;
    uint8_t _11[(0x4ca0 - 0x4a50) - sizeof(struct save_pokedex_t)];

    save_char_t waldas_phrase[SAVE_WALDAS_PHRASE_LENGTH];
    uint8_t _14[(0x4cb4 - 0x4ca0) - sizeof(save_char_t) * SAVE_WALDAS_PHRASE_LENGTH];

    struct save_box_data_t boxes;
    //last byte at 0xdf58
};

#endif
