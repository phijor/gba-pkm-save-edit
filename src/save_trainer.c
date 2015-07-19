#include <stdio.h>
#include <stdlib.h>

#include "save_trainer.h"
#include "save.h"
#include "save_unpacked.h"
#include "save_char_encoding.h"

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

void save_get_trainer_id(struct save_trainer_id_t* id,
                         union save_unpacked_t* save) {
    enum save_game_type_t game_type = save_get_gametype(save);
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
            fprintf(stderr, E("Game type not implemented."));
            exit(EXIT_FAILURE);
    }
}

void save_get_time_played(struct save_time_played_t* time,
                          union save_unpacked_t* save) {
    enum save_game_type_t game_type = save_get_gametype(save);
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
            fprintf(stderr, E("Game type not implemented."));
            exit(EXIT_FAILURE);
    }
}

int save_get_name(char name[8], union save_unpacked_t* save) {
    uint8_t* name_encoded = NULL;
    enum save_game_type_t game_type = save_get_gametype(save);
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
            fprintf(stderr, E("Game type not implemented."));
            exit(EXIT_FAILURE);
    }
    if (save_string_decode(name, name_encoded) > 8) {
        fprintf(stderr, W("Incorrectly terminated name."));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
