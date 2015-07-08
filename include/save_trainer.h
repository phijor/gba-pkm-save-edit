#ifndef SAVE_TRAINER_H
#define SAVE_TRAINER_H

#include "inttypes.h"

union save_unpacked_t;

uint32_t save_get_money(union save_unpacked_t* save);

enum save_player_gender_t save_get_trainer_gender(union save_unpacked_t* save);

struct save_trainer_id_t save_get_trainer_id(union save_unpacked_t* save);

const struct save_time_played_t* save_get_time_played(
    union save_unpacked_t* save);

int save_get_name(union save_unpacked_t* save, char name[8]);

#endif
