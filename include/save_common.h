#ifndef SAVE_COMMON_H
#define SAVE_COMMON_H

#include <inttypes.h>

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
    uint8_t name[8];
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
