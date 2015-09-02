#ifndef SAVE_TRAINER_H
#define SAVE_TRAINER_H

#include <inttypes.h>
#include "save_common.h"

union save_unpacked_t;

uint32_t save_trainer_money_get(union save_unpacked_t* save);

enum save_trainer_gender_t save_trainer_gender_get(union save_unpacked_t* save);

void save_trainer_id_get(struct save_trainer_id_t* id,
                         union save_unpacked_t* save);

void save_time_played_get(struct save_time_played_t* time,
                          union save_unpacked_t* save);

int save_trainer_name_get(char name[SAVE_TRAINER_NAME_SIZE], union save_unpacked_t* save);

#endif
