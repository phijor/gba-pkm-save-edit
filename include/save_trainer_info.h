#ifndef SAVE_TRAINER_INFO_H
#define SAVE_TRAINER_INFO_H
#include <inttypes.h>

struct trainer_id_t {
    uint16_t TID;
    uint16_t SID;
};

struct time_played_t {
    uint16_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t frames;
};

struct save_trainer_info_rs_t {
    uint8_t player_name[7];
    uint8_t padding0;

    uint8_t player_gender;
    uint8_t padding1;

    struct trainer_id_t trainer_id;
    struct time_played_t time_played;
    uint8_t padding2[0x99];

    uint32_t game_code;
};

struct save_trainer_info_e_t {
    uint8_t player_name[7];
    uint8_t padding0;

    uint8_t player_gender;
    uint8_t padding1;

    struct trainer_id_t trainer_id;
    struct time_played_t time_played;
    uint8_t padding2[0x99];

    uint32_t security_key;
};

struct save_trainer_info_frlg_t {
    uint8_t player_name[7];
    uint8_t padding0;

    uint8_t player_gender;
    uint8_t padding1;

    struct trainer_id_t trainer_id;
    struct time_played_t time_played;
    uint8_t padding2[0x99];

    uint32_t game_code;
    uint32_t security_key;
};

union save_trainer_info_container_t {
    struct save_trainer_info_rs_t   rs;
    struct save_trainer_info_e_t    e;
    struct save_trainer_info_frlg_t frlg;
};
#endif
