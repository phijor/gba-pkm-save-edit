#ifndef SAVE_LINK_H
#define SAVE_LINK_H

#include <inttypes.h>

#include "save_pokemon.h"

#define SAVE_LINK_TEAM_SIZE 3
#define SAVE_LINK_RESULTS 5

struct save_pokemon_minimal_t {
    uint16_t species;
    uint16_t held_item;
    uint16_t moves[SAVE_POKEMON_MOVES];
    uint8_t level;
    uint8_t _0[1];
    struct save_pokemon_data_ev_t EV;
    struct save_trainer_id_t OT_ID;
    uint32_t IV;
    uint32_t PID;
    save_char_t nickname[SAVE_POKEMON_NICKNAME_SIZE];
    uint8_t _1[2];
};

struct save_link_oppenent_header_t {
    uint8_t match_type;
    uint8_t trainer_class;
    uint8_t stage;
    uint8_t unknown;
    save_char_t OT_name[SAVE_TRAINER_NAME_SIZE];
    struct save_trainer_id_t OT_ID;
};

struct save_link_opponent_battletower_t {
    struct save_link_oppenent_header_t header;
    uint16_t phrases_intro[6];
    struct save_pokemon_minimal_t pokemon[SAVE_LINK_TEAM_SIZE];
    uint32_t checksum;
};

struct save_link_opponent_ecard_t {
    struct save_link_oppenent_header_t header;
    uint16_t phrases_intro[6];
    uint16_t phrases_win[6];
    uint8_t phrases_lose[6];
    struct save_pokemon_minimal_t pokemon[SAVE_LINK_TEAM_SIZE];
    uint32_t checksum;
};

struct save_link_results_t {
    save_char_t name[SAVE_TRAINER_NAME_SIZE];
    uint8_t _0[1];
    uint16_t TID;
    uint16_t wins;
    uint16_t losses;
    uint16_t draws;
};

#endif /* _____ #ifndef SAVE_LINK_H _____ */
