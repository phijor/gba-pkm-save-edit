#include <stdlib.h>

#include "message.h"
#include "save_trainer.h"
#include "save.h"
#include "save_unpacked.h"
#include "save_char_encoding.h"

enum save_exit_code_t save_trainer_money_get(union save_unpacked_t* save,
                                             uint32_t* money) {
    enum save_game_type_t game_type = save_gametype_get(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            *money = save->rusa.money ^ save->rusa.security_key;
        case FIRERED_LEAFGREEN:
            *money = save->frlg.money ^ save->frlg.security_key;
        case EMERALD:
            *money = save->emer.money ^ save->emer.security_key;
        default:
            return SAVE_EXIT_NOT_IMPLEMENTED;
    }
    return EXIT_SUCCESS;
}

enum save_exit_code_t save_trainer_gender_get(
    union save_unpacked_t* save, enum save_trainer_gender_t* gender) {
    enum save_game_type_t game_type = save_gametype_get(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            *gender = save->rusa.player.gender;
        case FIRERED_LEAFGREEN:
            *gender = save->frlg.player.gender;
        case EMERALD:
            *gender = save->emer.player.gender;
        default:
            return SAVE_EXIT_NOT_IMPLEMENTED;
    }
    return EXIT_SUCCESS;
}

enum save_exit_code_t save_trainer_id_get(union save_unpacked_t* save,
                                          struct save_trainer_id_t* id) {
    enum save_game_type_t game_type = save_gametype_get(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            *id = save->rusa.player.id;
            break;
        case FIRERED_LEAFGREEN:
            *id = save->frlg.player.id;
            break;
        case EMERALD:
            *id = save->emer.player.id;
            break;
        default:
            return SAVE_EXIT_NOT_IMPLEMENTED;
    }
    return EXIT_SUCCESS;
}

enum save_exit_code_t save_time_played_get(union save_unpacked_t* save,
                                           struct save_time_played_t* time) {
    enum save_game_type_t game_type = save_gametype_get(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            *time = save->rusa.player.time_played;
            break;
        case FIRERED_LEAFGREEN:
            *time = save->frlg.player.time_played;
            break;
        case EMERALD:
            *time = save->emer.player.time_played;
            break;
        default:
            return SAVE_EXIT_NOT_IMPLEMENTED;
    }
    return EXIT_SUCCESS;
}

enum save_exit_code_t save_trainer_name_get(union save_unpacked_t* save,
                                            char name[SAVE_TRAINER_NAME_SIZE]) {
    save_char_t* name_encoded = NULL;
    enum save_game_type_t game_type = save_gametype_get(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            name_encoded = save->rusa.player.name;
            break;
        case FIRERED_LEAFGREEN:
            name_encoded = save->frlg.player.name;
            break;
        case EMERALD:
            name_encoded = save->emer.player.name;
            break;
        default:
            return SAVE_EXIT_NOT_IMPLEMENTED;
    }
    save_string_decode(name, name_encoded, SAVE_TRAINER_NAME_SIZE);
    return SAVE_EXIT_SUCCESS;
}
