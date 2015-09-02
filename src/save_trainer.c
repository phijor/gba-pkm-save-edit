#include <stdlib.h>

#include "message.h"
#include "save_trainer.h"
#include "save.h"
#include "save_unpacked.h"
#include "save_char_encoding.h"

uint32_t save_trainer_money_get(union save_unpacked_t* save) {
    enum save_game_type_t game_type = save_gametype_get(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            return save->rusa.money ^ save->rusa.security_key;
        case FIRERED_LEAFGREEN:
            return save->frlg.money ^ save->frlg.security_key;
        case EMERALD:
            return save->emer.money ^ save->emer.security_key;
        default:
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }
}

enum save_trainer_gender_t save_trainer_gender_get(union save_unpacked_t* save) {
    enum save_game_type_t game_type = save_gametype_get(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            return save->rusa.player.gender;
        case FIRERED_LEAFGREEN:
            return save->frlg.player.gender;
        case EMERALD:
            return save->emer.player.gender;
        default:
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }
}

void save_trainer_id_get(struct save_trainer_id_t* id,
                         union save_unpacked_t* save) {
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
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }
}

void save_time_played_get(struct save_time_played_t* time,
                          union save_unpacked_t* save) {
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
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }
}

int save_trainer_name_get(char name[SAVE_TRAINER_NAME_SIZE], union save_unpacked_t* save) {
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
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }
    save_string_decode(name, name_encoded, SAVE_TRAINER_NAME_SIZE);
    return EXIT_SUCCESS;
}
