#ifndef SAVE_POKEMON_H
#define SAVE_POKEMON_H

#include <stddef.h>
#include <inttypes.h>
#include "save_common.h"

struct save_pokemon_data_permutation_t {
    size_t growth;
    size_t attacks;
    size_t condition;
    size_t misc;
};

extern const struct save_pokemon_data_permutation_t
    save_pokemon_data_permutations[24];

struct save_pokemon_data_growth_t {
    uint16_t species;
    uint16_t item_held;
    uint32_t experience_points;
    uint8_t pp_bonuses;
    uint8_t friendship;
};

struct save_pokemon_data_attacks_t {
    uint16_t moves[4];
    uint8_t pp_ups[4];
};

struct save_pokemon_data_condition_t {
    uint8_t ev_hp;
    uint8_t ev_atk;
    uint8_t ev_def;
    uint8_t ev_spe;
    uint8_t ev_spa;
    uint8_t ev_spd;
    uint8_t coolness;
    uint8_t beauty;
    uint8_t cuteness;
    uint8_t smartness;
    uint8_t toughness;
    uint8_t feel;
};

struct save_pokemon_data_misc_t {
    uint8_t pokerus;
    uint8_t met_location;
    uint16_t origin_info;
    uint8_t iv_egg_ability;
    uint32_t ribbons_obedience;
};

union save_pokemon_data_t {
    struct save_pokemon_data_growth_t growth;
    struct save_pokemon_data_attacks_t attacks;
    struct save_pokemon_data_condition_t condition;
    struct save_pokemon_data_misc_t misc;
};

struct save_pokemon_data_ordered_t {
    struct save_pokemon_data_growth_t* growth;
    struct save_pokemon_data_attacks_t* attacks;
    struct save_pokemon_data_condition_t* condition;
    struct save_pokemon_data_misc_t* misc;
};

struct save_pokemon_boxed_t {
    uint32_t PID;
    struct save_trainer_id_t OT_ID;
    uint8_t nickname[10];
    uint16_t language;
    uint8_t OT_name[7];
    uint8_t markings;
    uint16_t checksum;
    uint16_t _0[1];
    union save_pokemon_data_t data[4];
};

struct save_pokemon_t {
    struct save_pokemon_boxed_t boxed;
    uint32_t status_condition;
    uint8_t level;
    uint8_t pokerus_remaining;
    uint16_t hp_current;
    uint16_t hp_total;
    uint16_t attack;
    uint16_t defense;
    uint16_t speed;
    uint16_t special_attack;
    uint16_t special_defense;
};

uint32_t save_pokemon_get_crypt_key(struct save_pokemon_boxed_t* pokemon);
void save_pokemon_xor_crypt(struct save_pokemon_boxed_t* pokemon);
void save_pokemon_order_data(struct save_pokemon_boxed_t* pokemon,
                             struct save_pokemon_data_ordered_t* odered);
int save_pokemon_check_data_integrity(struct save_pokemon_boxed_t* pokemon);

#endif
