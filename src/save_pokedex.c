#include <stdio.h>
#include <stdlib.h>

#include "save_pokedex.h"
#include "save.h"
#include "save_unpacked.h"

int save_pokedex_search(struct save_pokedex_t* pokedex, uint16_t index) {
    return (pokedex->data[index >> 3] >> (index % 8)) & 1;
}

enum save_pokedex_status_t save_get_pokedex_entry(union save_unpacked_t* save,
                                                  uint16_t index) {
    enum save_pokedex_status_t status = POKEDEX_ERROR;
    struct save_pokedex_t* seen[3] = {NULL, NULL, NULL};

    enum save_game_type_t game_type = save_get_gametype(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            seen[0] = &(save->rusa.pokedex_seen_a);
            seen[1] = &(save->rusa.pokedex_seen_b);
            seen[2] = &(save->rusa.pokedex_seen_c);
            break;
        default:
            fprintf(stderr, E("Game type not implemented."));
            exit(EXIT_FAILURE);
    }
    int is_seen = 1;
    for (size_t i = 0; i < 3; i++) {
        is_seen = save_pokedex_search(seen[i], index) && is_seen;
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
        default:
            fprintf(stderr, E("Game type not implemented."));
            exit(EXIT_FAILURE);
    }
    if (save_pokedex_search(owned, index)) {
        status = OWNED;
    }

    return status;
}

void save_pokedex_basic_set(struct save_pokedex_t* pokedex, uint16_t index) {
    pokedex->data[index >> 3] |= 1 << (index % 8);
}

void save_pokedex_clear_entry(struct save_pokedex_t* pokedex, uint16_t index) {
    pokedex->data[index >> 3] &= ~(1 << (index % 8));
}

int save_set_pokedex_entry(union save_unpacked_t* save, uint16_t index,
                           enum save_pokedex_status_t status) {
    enum save_game_type_t game_type = save_get_gametype(save);
    struct save_pokedex_t* pokedex_seen[3] = {NULL, NULL, NULL};
    struct save_pokedex_t* pokedex_owned = NULL;
    switch (game_type) {
        case RUBY_SAPPHIRE:
            pokedex_seen[0] = &(save->rusa.pokedex_seen_a);
            pokedex_seen[1] = &(save->rusa.pokedex_seen_b);
            pokedex_seen[2] = &(save->rusa.pokedex_seen_c);
            pokedex_owned = &(save->rusa.pokedex_owned);
            break;
        default:
            fprintf(stderr, E("Game type not implemented."));
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
            save_pokedex_clear_entry(pokedex_owned, index);
            for (size_t i = 0; i < 3; i++) {
                save_pokedex_clear_entry(pokedex_seen[i], index);
            }
            break;
        default:
            fprintf(stderr, E("Cannot set requested status (%d) in Pokedex."),
                    status);
            return POKEDEX_ERROR;
    }
    return POKEDEX_SUCCESS;
}
