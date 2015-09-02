#ifndef SAVE_POKEMON_H
#define SAVE_POKEMON_H

#include <stddef.h>
#include <inttypes.h>
#include "save_common.h"

#define SAVE_POKEMON_NICKNAME_SIZE 10
#define SAVE_POKEMON_OT_NAME_SIZE 7
#define SAVE_POKEMON_ATTACKS 4

#define SAVE_POKEMON_MARK_CIRCLE (1 << 0)
#define SAVE_POKEMON_MARK_SQUARE (1 << 1)
#define SAVE_POKEMON_MARK_TRIANG (1 << 2)
#define SAVE_POKEMON_MARK_HEART  (1 << 3)

#define SAVE_POKEMON_MET_LEVEL (0x3f << 0)
#define SAVE_POKEMON_ORIG_GAME (0x0f << 7)
#define SAVE_POKEMON_BALL      (0x0f << 11)
#define SAVE_POKEMON_OT_GENDER (0x01 << 15)

#define SAVE_POKEMON_MET_LEVEL_SHIFT 0
#define SAVE_POKEMON_ORIG_GAME_SHIFT 7
#define SAVE_POKEMON_BALL_SHIFT      11
#define SAVE_POKEMON_OT_GENDER_SHIFT 15

enum save_pokemon_language_t { SAVE_LANG_BASE = 0x200,
    SAVE_LANG_JAPANESE,
    SAVE_LANG_ENGLISH,
    SAVE_LANG_FRENCH,
    SAVE_LANG_ITALIAN,
    SAVE_LANG_GERMAN,
    SAVE_LANG_KOREAN,
    SAVE_LANG_SPANISH,
};

enum save_pokerus_status_t {
    SAVE_POKERUS_NONE,
    SAVE_POKERUS_INFECTED,
    SAVE_POKERUS_CURED,
    SAVE_POKERUS_INVALID
};

enum save_pokemon_game_of_origin_t {
    SAVE_ORIG_COL_BONUS_DISK = 0,
    SAVE_ORIG_SAPPHIRE,
    SAVE_ORIG_RUBY,
    SAVE_ORIG_EMERALD,
    SAVE_ORIG_FIRERED,
    SAVE_ORIG_LEAFGREEN,
    SAVE_ORIG_COL_XD = 15,
};

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

struct save_pokemon_data_ev_t {
    uint8_t HP;
    uint8_t ATK;
    uint8_t DEF;
    uint8_t SPE;
    uint8_t SPA;
    uint8_t SPD;
};

struct save_pokemon_data_contest_t {
    uint8_t coolness;
    uint8_t beauty;
    uint8_t cuteness;
    uint8_t smartness;
    uint8_t toughness;
    uint8_t feel;
};

struct save_pokemon_data_condition_t {
    struct save_pokemon_data_ev_t EV;
    struct save_pokemon_data_contest_t contest;
};

struct save_pokemon_data_misc_t {
    uint8_t pokerus;
    uint8_t met_location;
    uint16_t origin_info;
    uint32_t iv_egg_ability;
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
    uint8_t nickname[SAVE_POKEMON_NICKNAME_SIZE];
    uint16_t language;
    uint8_t OT_name[SAVE_POKEMON_OT_NAME_SIZE];
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

uint32_t save_pokemon_crypt_key_set(struct save_pokemon_boxed_t* pokemon);
void save_pokemon_xor_crypt(struct save_pokemon_boxed_t* pokemon);
void save_pokemon_order_data(struct save_pokemon_boxed_t* pokemon,
                             struct save_pokemon_data_ordered_t* ordered);
int save_pokemon_data_integrity_check(struct save_pokemon_boxed_t* pokemon);

size_t save_pokemon_nickname_get(struct save_pokemon_boxed_t* pokemon, char* nickname);
size_t save_pokemon_ot_name_get(struct save_pokemon_boxed_t* pokemon, char* ot_name);

uint8_t save_pokemon_pp_bonuses_get(struct save_pokemon_data_ordered_t* pkm_data,
                                    size_t move);

int save_pokemon_pokerus_remaining_get(
    struct save_pokemon_data_ordered_t* pkm_data);

int save_pokemon_pokerus_max_days_get(
    struct save_pokemon_data_ordered_t* pkm_data);

uint8_t save_pokemon_pokerus_strain_get(
    struct save_pokemon_data_ordered_t* pkm_data);

enum save_pokerus_status_t save_pokemon_pokerus_status_get(
    struct save_pokemon_data_ordered_t* pkm_data);

uint8_t save_pokemon_met_level_get(
    struct save_pokemon_data_ordered_t* pkm_data);

enum save_pokemon_game_of_origin_t save_pokemon_origin_get(
    struct save_pokemon_data_ordered_t* pkm_data);

uint8_t save_pokemon_ball_get(struct save_pokemon_data_ordered_t* pkm_data);

enum save_trainer_gender_t save_pokemon_ot_gender_get(
    struct save_pokemon_data_ordered_t* pkm_data);

#endif
