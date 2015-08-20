#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "message.h"
#include "save.h"
#include "save_unpacked.h"

int save_pokemon_get_team(
    union save_unpacked_t* save, struct save_pokemon_boxed_t* team) {
    struct save_pokemon_t* team_extended;
    enum save_game_type_t game_type = save_get_gametype(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            team_extended = save->rusa.team_pokemon;
            break;
        case FIRERED_LEAFGREEN:
            team_extended = save->frlg.team_pokemon;
            break;
        case EMERALD:
            team_extended = save->emer.team_pokemon;
            break;
        default:
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }

    assert(team != NULL);
    for (size_t i = 0; i < 6; i++) {
        memcpy(&team[i], &team_extended[i].boxed, sizeof(struct save_pokemon_boxed_t));
    }
    return EXIT_SUCCESS;
}

int save_pokemon_slot_is_empty(struct save_pokemon_boxed_t* pokemon) {
    return pokemon->nickname[0] == '\0' && pokemon->language == 0;
}
