#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "message.h"
#include "save.h"
#include "save_unpacked.h"

int save_pokemon_get_party(
    union save_unpacked_t* save, struct save_pokemon_boxed_t* party) {
    struct save_pokemon_t* party_extended;
    enum save_game_type_t game_type = save_get_gametype(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            party_extended = save->rusa.party;
            break;
        case FIRERED_LEAFGREEN:
            party_extended = save->frlg.party;
            break;
        case EMERALD:
            party_extended = save->emer.party;
            break;
        default:
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }

    assert(party != NULL);
    for (size_t i = 0; i < 6; i++) {
        memcpy(&party[i], &party_extended[i].boxed, sizeof(struct save_pokemon_boxed_t));
    }
    return EXIT_SUCCESS;
}

int save_pokemon_slot_is_empty(struct save_pokemon_boxed_t* pokemon) {
    return pokemon->nickname[0] == '\0' && pokemon->language == 0;
}
