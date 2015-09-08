#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "message.h"
#include "save_storage.h"
#include "save.h"
#include "save_unpacked.h"
#include "save_boxes.h"
#include "save_char_encoding.h"

int save_storage_party_get(union save_unpacked_t* save,
                           struct save_pokemon_t* party) {
    struct save_pokemon_extended_t* party_extended;
    enum save_game_type_t game_type = save_gametype_get(save);
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
    for (size_t i = 0; i < SAVE_PARTY_SLOTS; i++) {
        memcpy(&party[i], &party_extended[i].boxed,
               sizeof(struct save_pokemon_t));
    }
    return EXIT_SUCCESS;
}

int save_storage_box_get(union save_unpacked_t* save, size_t index,
                         struct save_box_unpacked_t* box) {
    if (index >= SAVE_BOXES) {
        message("E", "Cannot access box %ld: Out of range.\n", index);
        return EXIT_FAILURE;
    }
    save_char_t* name_ptr;
    struct save_pokemon_t* pkm_ptr;

    enum save_game_type_t game_type = save_gametype_get(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            box->wallpaper = save->rusa.boxes.wallpapers[index];
            name_ptr = save->rusa.boxes.names[index];
            pkm_ptr = save->rusa.boxes.pokemon[index];
            break;
        case FIRERED_LEAFGREEN:
            box->wallpaper = save->frlg.boxes.wallpapers[index];
            name_ptr = save->frlg.boxes.names[index];
            pkm_ptr = save->rusa.boxes.pokemon[index];
            break;
        case EMERALD:
            box->wallpaper = save->emer.boxes.wallpapers[index];
            name_ptr = save->emer.boxes.names[index];
            pkm_ptr = save->rusa.boxes.pokemon[index];
            break;
        default:
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }

    assert(box != NULL);
    save_string_decode(box->name, name_ptr, SAVE_BOX_NAME_LENGTH);
    memcpy(&box->pokemon, pkm_ptr,
           SAVE_BOX_SLOTS * sizeof(struct save_pokemon_t));
    return EXIT_SUCCESS;
}

uint32_t save_storage_party_size_get(union save_unpacked_t* save) {
    enum save_game_type_t game_type = save_gametype_get(save);
    switch (game_type) {
        case RUBY_SAPPHIRE:
            return save->rusa.party_size;
        case FIRERED_LEAFGREEN:
            return save->frlg.party_size;
        case EMERALD:
            return save->emer.party_size;
        default:
            message("E", "Game type not implemented.\n");
            exit(EXIT_FAILURE);
    }
}

int save_storage_slot_is_empty(struct save_pokemon_t* pokemon) {
    return pokemon->occupancy == SAVE_STORAGE_EMPTY;
}
