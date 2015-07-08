#include <stdio.h>
#include <stdlib.h>

#include "save_trainer.h"
#include "save.h"
#include "save_unpacked.h"

uint32_t save_get_money(union save_unpacked_t* save) {
    enum save_game_type_t game_type = save_get_gametype(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            return save->rusa.money ^ save->rusa.security_key;
        case FIRERED_LEAFGREEN:
            return save->frlg.money ^ save->frlg.security_key;
        case EMERALD:
            return save->emer.money ^ save->emer.security_key;
        default:
            fprintf(stderr, E("Game type not implemented."));
            exit(EXIT_FAILURE);
    }
}

enum save_player_gender_t save_get_trainer_gender(union save_unpacked_t* save) {
    enum save_game_type_t game_type = save_get_gametype(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            return save->rusa.player.gender;
        case FIRERED_LEAFGREEN:
            return save->frlg.player.gender;
        case EMERALD:
            return save->emer.player.gender;
        default:
            fprintf(stderr, E("Game type not implemented."));
            exit(EXIT_FAILURE);
    }
}

struct save_trainer_id_t save_get_trainer_id(union save_unpacked_t* save) {
    enum save_game_type_t game_type = save_get_gametype(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            return save->rusa.player.id;
        case FIRERED_LEAFGREEN:
            return save->frlg.player.id;
        case EMERALD:
            return save->emer.player.id;
        default:
            fprintf(stderr, E("Game type not implemented."));
            exit(EXIT_FAILURE);
    }
}

const struct save_time_played_t* save_get_time_played(
    union save_unpacked_t* save) {
    enum save_game_type_t game_type = save_get_gametype(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            return &(save->rusa.player.time_played);
        case FIRERED_LEAFGREEN:
            return &(save->frlg.player.time_played);
        case EMERALD:
            return &(save->emer.player.time_played);
        default:
            fprintf(stderr, E("Game type not implemented."));
            exit(EXIT_FAILURE);
    }
}
