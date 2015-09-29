#ifndef SAVE_TRAINER_H
#define SAVE_TRAINER_H

#include <inttypes.h>
#include "save_common.h"

union save_unpacked_t;

enum save_exit_code_t save_trainer_money_get(union save_unpacked_t* save,
                                             uint32_t* money);

enum save_exit_code_t save_trainer_gender_get(
    union save_unpacked_t* save, enum save_trainer_gender_t* gender);

enum save_exit_code_t save_trainer_id_get(union save_unpacked_t* save,
                                          struct save_trainer_id_t* id);

enum save_exit_code_t save_time_played_get(union save_unpacked_t* save,
                                           struct save_time_played_t* time);

enum save_exit_code_t save_trainer_name_get(union save_unpacked_t* save,
                                            char name[SAVE_TRAINER_NAME_SIZE]);

#endif
