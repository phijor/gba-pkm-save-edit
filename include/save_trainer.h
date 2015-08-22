#ifndef SAVE_TRAINER_H
#define SAVE_TRAINER_H

#include <inttypes.h>
#include "save_common.h"
#define SAVE_TRAINER_NAME_SIZE 8

union save_unpacked_t;

uint32_t save_get_money(union save_unpacked_t* save);

enum save_player_gender_t save_get_trainer_gender(union save_unpacked_t* save);

void save_get_trainer_id(struct save_trainer_id_t* id,
                         union save_unpacked_t* save);

void save_get_time_played(struct save_time_played_t* time,
                          union save_unpacked_t* save);

int save_get_name(char name[SAVE_TRAINER_NAME_SIZE], union save_unpacked_t* save);

#endif
