#include <stdlib.h>

#include "message.h"
#include "save_pokedex.h"
#include "save.h"
#include "save_unpacked.h"

int save_pokedex_basic_get(struct save_pokedex_t* pokedex, uint16_t index) {
    return (pokedex->data[index >> 3] >> (index % 8)) & 1;
}

void save_pokedex_basic_set(struct save_pokedex_t* pokedex, uint16_t index) {
    pokedex->data[index >> 3] |= 1 << (index % 8);
}

void save_pokedex_basic_clear(struct save_pokedex_t* pokedex, uint16_t index) {
    pokedex->data[index >> 3] &= ~(1 << (index % 8));
}

enum save_pokedex_status_t save_pokedex_get(union save_unpacked_t* save,
                                                  uint16_t index) {
    enum save_pokedex_status_t status = POKEDEX_ERROR;
    struct save_pokedex_t* seen[3] = {NULL, NULL, NULL};

    enum save_game_type_t game_type = save_gametype_get(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            seen[0] = &(save->rusa.pokedex_seen_a);
            seen[1] = &(save->rusa.pokedex_seen_b);
            seen[2] = &(save->rusa.pokedex_seen_c);
            break;
        case FIRERED_LEAFGREEN:
            seen[0] = &(save->frlg.pokedex_seen_a);
            seen[1] = &(save->frlg.pokedex_seen_b);
            seen[2] = &(save->frlg.pokedex_seen_c);
            break;
        case EMERALD:
            seen[0] = &(save->emer.pokedex_seen_a);
            seen[1] = &(save->emer.pokedex_seen_b);
            seen[2] = &(save->emer.pokedex_seen_c);
            break;
        default:
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }
    int is_seen = 1;
    for (size_t i = 0; i < 3; i++) {
        is_seen = save_pokedex_basic_get(seen[i], index) && is_seen;
    }
    if (is_seen) {
        status = SEEN;
    } else {
        return UNSEEN;
    }

    struct save_pokedex_t* owned = NULL;
    switch (game_type) {
        case RUBY_SAPPHIRE:
            owned = &(save->rusa.pokedex_owned);
            break;
        case FIRERED_LEAFGREEN:
            owned = &(save->frlg.pokedex_owned);
            break;
        case EMERALD:
            owned = &(save->emer.pokedex_owned);
            break;
        default:
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }
    if (save_pokedex_basic_get(owned, index)) {
        status = OWNED;
    }

    return status;
}

int save_pokedex_set(union save_unpacked_t* save, uint16_t index,
                           enum save_pokedex_status_t status) {
    enum save_game_type_t game_type = save_gametype_get(save);
    struct save_pokedex_t* pokedex_seen[3] = {NULL, NULL, NULL};
    struct save_pokedex_t* pokedex_owned = NULL;
    switch (game_type) {
        case RUBY_SAPPHIRE:
            pokedex_seen[0] = &(save->rusa.pokedex_seen_a);
            pokedex_seen[1] = &(save->rusa.pokedex_seen_b);
            pokedex_seen[2] = &(save->rusa.pokedex_seen_c);
            pokedex_owned = &(save->rusa.pokedex_owned);
            break;
        case FIRERED_LEAFGREEN:
            pokedex_seen[0] = &(save->frlg.pokedex_seen_a);
            pokedex_seen[1] = &(save->frlg.pokedex_seen_b);
            pokedex_seen[2] = &(save->frlg.pokedex_seen_c);
            pokedex_owned = &(save->frlg.pokedex_owned);
            break;
        case EMERALD:
            pokedex_seen[0] = &(save->emer.pokedex_seen_a);
            pokedex_seen[1] = &(save->emer.pokedex_seen_b);
            pokedex_seen[2] = &(save->emer.pokedex_seen_c);
            pokedex_owned = &(save->emer.pokedex_owned);
            break;
        default:
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }
    switch (status) {
        case OWNED:
            save_pokedex_basic_set(pokedex_owned, index);
            /* Missing break-statement is important, as every Pokemon that is
             * owned/caught has to be seen also.
             */
        case SEEN:
            for (size_t i = 0; i < 3; i++) {
                save_pokedex_basic_set(pokedex_seen[i], index);
            }
            break;
        case UNSEEN:
            save_pokedex_basic_clear(pokedex_owned, index);
            for (size_t i = 0; i < 3; i++) {
                save_pokedex_basic_clear(pokedex_seen[i], index);
            }
            break;
        default:
            message("E", "Unknown status %d. Could not set in Pokédex.\n", status);
            return POKEDEX_ERROR;
    }
    return POKEDEX_SUCCESS;
}
