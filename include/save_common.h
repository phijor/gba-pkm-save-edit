#ifndef SAVE_COMMON_H
#define SAVE_COMMON_H

#include <inttypes.h>

#define SAVE_TRAINER_NAME_SIZE 8
#define SAVE_TRAINER_NAME_SIZE_UNPACKED (SAVE_TRAINER_NAME_SIZE + 1)

typedef unsigned char save_char_t;

enum save_trainer_gender_t {
    MALE = 0,
    FEMALE = 1,
};

struct save_trainer_id_t {
    uint16_t TID;
    uint16_t SID;
};

struct save_time_played_t {
    uint16_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t frames;
};

struct save_trainer_info_t {
    save_char_t name[SAVE_TRAINER_NAME_SIZE];
    uint8_t gender;
    uint8_t _0[1];
    struct save_trainer_id_t id;
    struct save_time_played_t time_played;
};

struct save_item_t {
    uint16_t index;
    uint16_t quantity;
};

#endif
