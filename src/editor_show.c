#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdlib.h>
#include <sys/types.h>

#include "message.h"

#include "editor_show.h"
#include "editor.h"
#include "editor_parse.h"
#include "editor_lut.h"

#include "save.h"
#include "save_unpacked.h"

#include "save_common.h"
#include "save_pokedex.h"
#include "save_trainer.h"
#include "save_pokemon.h"
#include "save_storage.h"
#include "save_boxes.h"
#include "save_moves.h"

int editor_show(union save_unpacked_t* save, int argc, char* const* argv) {
    const struct editor_call_t commands[] = {
        {.name = "pokedex", .exec = &editor_show_pokedex},
        {.name = "pokemon", .exec = &editor_show_pokemon},
        {.name = "trainer", .exec = &editor_show_trainer},
        {.name = "map", .exec = &editor_show_map},
        {.name = NULL, .exec = NULL},
    };
    return editor_call(save, commands, argc, argv);
}

int editor_show_map(union save_unpacked_t* save, int argc, char* const* argv) {
    if (save_gametype_get(save) != EMERALD) {
        message("E", "Feature requires Emerald save.\n");
        return -1;
    }
    message("I", "Map info:\n");
    message("*", "x: %d\n", save->emer.map.x++);
    message("*", "y: %d\n", save->emer.map.y++);

    return 0;
}

int editor_show_pokedex(union save_unpacked_t* save, int argc,
                        char* const* argv) {
    const char* status_string[] = {
            [UNSEEN] = "Unseen",    [SEEN] = "Seen",      [OWNED] = "Caught",
            [POKEDEX_SUCCESS] = "", [POKEDEX_ERROR] = "",
    };

    struct editor_range_t range = {
        .min = 1, .max = SAVE_DEX_SIZE,
    };

    if (argc > 0 && argv[0] != NULL) {
        editor_parse_range(&range, argv[0]);
    } else {
        range.lower = range.min;
        range.upper = range.max;
    }

    for (ssize_t i = range.lower; i <= range.upper; i++) {
        enum save_pokedex_status_t status = save_pokedex_get(save, i - 1);
        if (status == POKEDEX_ERROR) {
            message("E", "Pokedex data at index #%03ld is invalid.\n", i);
            return EXIT_FAILURE;
        }
        message("*", "#%03ld: %s\n", i, status_string[status]);
    }
    return EXIT_SUCCESS;
}

int editor_show_trainer(union save_unpacked_t* save, int argc,
                        char* const* argv) {
    {
        char name[SAVE_TRAINER_NAME_SIZE_UNPACKED] = {'\0'};
        save_trainer_name_get(save, name);
        message("*", "Name: %s\n", name);
    }
    {
        struct save_trainer_id_t id;
        save_trainer_id_get(save, &id);
        message("*", "Trainer ID (TID): %05u\n", id.TID);
        message("*", "Secret ID  (SID): %05u\n", id.SID);
    }
    {
        struct save_time_played_t time;
        save_time_played_get(save, &time);
        message("*", "Time played: %03u:%02u:%02u/%02u\n", time.hours,
                time.minutes, time.seconds, time.frames);
    }
    {
        uint32_t money;
        save_trainer_money_get(save, &money);
        message("*", "Money: %u\n", money);
    }
    return EXIT_SUCCESS;
}

int editor_show_pokemon(union save_unpacked_t* save, int argc,
                        char* const* argv) {
    const struct editor_call_t commands[] = {
        {.name = "party", .exec = &editor_show_pokemon_party},
        {.name = "box", .exec = &editor_show_pokemon_box},
        {.name = NULL, .exec = NULL},
    };
    return editor_call(save, commands, argc, argv);
}

int editor_show_pokemon_party(union save_unpacked_t* save, int argc,
                              char* const* argv) {
    int optind = 0;
    struct editor_range_t range = {
        .min = 1, .max = SAVE_PARTY_SLOTS,
    };

    if (argc > optind && argv[optind] != NULL) {
        editor_parse_range(&range, argv[optind]);
        optind++;
    } else {
        range.lower = range.min;
        range.upper = range.max;
    }

    long int party_size = save_storage_party_size_get(save);
    if (range.upper > party_size) {
        message("W", "Only %ld out of 6 slots are/is occupied.\n", party_size);
        range.upper = party_size;
    }

    struct save_pokemon_t party[SAVE_PARTY_SLOTS];
    save_storage_party_get(save, party);

    for (ssize_t i = range.lower; i <= range.upper; i++) {
        message("+", "Party Pokemon #%ld:\n", i);
        editor_show_pokemon_info(&party[i - 1]);
        message_indent(-1);
    }
    return EXIT_SUCCESS;
}

int editor_show_pokemon_box(union save_unpacked_t* save, int argc,
                            char* const* argv) {
    int optind = 0;
    struct editor_range_t boxes = {
        .min = 1, .max = SAVE_BOXES,
    };
    struct editor_range_t slots = {
        .min = 1, .max = SAVE_BOX_SLOTS,
    };

    if (argc > optind && argv[optind] != NULL) {
        editor_parse_range(&boxes, argv[optind]);
        optind++;
    } else {
        boxes.lower = boxes.min;
        boxes.upper = boxes.max;
    }
    if (argc > optind && argv[optind] != NULL) {
        editor_parse_range(&slots, argv[optind]);
        optind++;
    } else {
        slots.lower = slots.min;
        slots.upper = slots.max;
    }

    for (ssize_t box_ind = boxes.lower; box_ind <= boxes.upper; box_ind++) {
        struct save_box_unpacked_t box;
        save_storage_box_get(save, box_ind - 1, &box);
        for (ssize_t slot = slots.lower; slot <= slots.upper; slot++) {
            message("+", "Box \'%s\', slot #%ld:\n", box.name, slot);
            int ret = editor_show_pokemon_info(&box.pokemon[slot - 1]);
            if (ret == EXIT_FAILURE) {
                message("*", "Empty slot.\n");
            }
            message_indent(-1);
        }
    }
    return EXIT_SUCCESS;
}

int editor_show_pokemon_info(struct save_pokemon_t* pokemon) {
    if (save_storage_slot_is_empty(pokemon)) {
        return EXIT_FAILURE;
    }

    struct save_pokemon_decrypted_t pkm_data = {NULL, NULL, NULL, NULL, NULL};
    save_pokemon_decrypt(pokemon, &pkm_data);

    {
        enum save_species_t species = pkm_data.growth->species;

        if (species >= SAVE_SPECIES) {
            species = SAVE_SPECIES_NONE;
        }
        message("*+", "Species: %s\n", editor_species_names[species]);
        if (save_storage_slot_is_egg(pokemon) ||
            save_pokemon_is_egg(&pkm_data)) {
            message("*", "Egg: yes (%#02x)\n", pokemon->occupancy);
        }
        message_indent(-1);
    }
    {
        char nickname[SAVE_POKEMON_NICKNAME_SIZE_UNPACKED] = {'\0'};
        save_pokemon_nickname_get(pokemon, nickname);
        message("*", "Nickname: %s\n", nickname);
    }
    {
        char ot_name[SAVE_TRAINER_NAME_SIZE_UNPACKED] = {'\0'};
        save_pokemon_ot_name_get(pokemon, ot_name);
        message("*+", "Original Trainer (OT): %s\n", ot_name);
        message("*", "Trainer ID (TID): %05d\n", pokemon->OT_ID.TID);
        message("*-", "Secret ID (SID):  %05d\n", pokemon->OT_ID.SID);
    }
    {
        enum save_items_t item = pkm_data.growth->item_held;
        if (item >= SAVE_ITEMS) {
            item = SAVE_ITEM_NONE;
        }
        message("*", "Held item: %s\n", editor_item_names[item]);
    }
    {
        static const char* shininess[] = {
            "not shiny", ANSI_COLOR_YELLOW "shiny" ANSI_COLOR_RESET,
        };

        size_t is_shiny = save_pokemon_is_shiny(pokemon) ? 1 : 0;
        message("*+", "PID: %#08x\n", pokemon->PID);
        message("*", "Shininess: %s\n", shininess[is_shiny]);
        message("*-", "Nature:    %s\n",
                editor_nature_names[save_pokemon_nature_get(pokemon)]);
    }
    {
        enum save_pokemon_language_t language = pokemon->language;
        message("*", "Language: %s (%#04x)\n", editor_language_names[language],
                pokemon->language);
    }
    {
        struct save_pokemon_data_ev_t* EV = &pkm_data.condition->EV;
        message("*+", "Effort Values (EV):\n");
        message("*", "HP:          %3u\n", EV->HP);
        message("*", "Attack:      %3u\n", EV->ATK);
        message("*", "Defense:     %3u\n", EV->DEF);
        message("*", "Sp. Attack:  %3u\n", EV->SPA);
        message("*", "Sp. Defense: %3u\n", EV->SPD);
        message("*-", "Speed:       %3u\n", EV->SPE);
    }
    {
        struct save_pokemon_data_contest_t* contest =
            &pkm_data.condition->contest;
        message("*+", "Contest stats:\n");
        message("*", "Coolness:  %3u\n", contest->coolness);
        message("*", "Beauty:    %3u\n", contest->beauty);
        message("*", "Cuteness:  %3u\n", contest->cuteness);
        message("*", "Smartness: %3u\n", contest->smartness);
        message("*", "Toughness: %3u\n", contest->toughness);
        message("*-", "Feel:      %3u\n", contest->feel);
    }
    {
        message("*+", "Growth:\n");
        message("*", "Experience points (EP): %7u\n",
                pkm_data.growth->experience_points);
        message("*-", "Friendship:             %7u\n",
                pkm_data.growth->friendship);
    }
    {
        const char* pkrs_status[] = {
                [SAVE_POKERUS_NONE] = "None",
                [SAVE_POKERUS_INFECTED] = "Infected",
                [SAVE_POKERUS_CURED] = "Cured",
                [SAVE_POKERUS_INVALID] = "INVALID!",
        };

        message("*", "Pokerus: %s (%#03x)\n",
                pkrs_status[save_pokemon_pokerus_status_get(&pkm_data)],
                pkm_data.misc->pokerus);
        int remaining = save_pokemon_pokerus_remaining_get(&pkm_data);
        if (remaining) {
            message_indent(+1);
            message("*", "Day(s) remaining: %u/%u\n", remaining,
                    save_pokemon_pokerus_max_days_get(&pkm_data));
            message_indent(-1);
        }
    }
    {
        message("*+", "Moves:\n");
        for (size_t i = 0; i < SAVE_POKEMON_MOVES; i++) {
            enum save_move_t move = pkm_data.attacks->moves[i];
            if (move >= SAVE_MOVES) {
                move = SAVE_MOVE_NONE;
            }
            message("*+", "#%lu: %s\n", i + 1, editor_move_names[move]);
            if (move != SAVE_MOVE_NONE) {
                message("*", "PP:    %3u\n", pkm_data.attacks->pp_ups[i]);
                message("*", "PP Up: %u/3\n",
                        save_pokemon_pp_bonuses_get(&pkm_data, i));
            }
            message_indent(-1);
        }
        message_indent(-1);
    }
    {
        char markings[] = {"----"};
        if (pokemon->markings & SAVE_POKEMON_MARK_CIRCLE) {
            markings[0] = 'c';
        }
        if (pokemon->markings & SAVE_POKEMON_MARK_SQUARE) {
            markings[1] = 's';
        }
        if (pokemon->markings & SAVE_POKEMON_MARK_TRIANG) {
            markings[2] = 't';
        }
        if (pokemon->markings & SAVE_POKEMON_MARK_HEART) {
            markings[3] = 'h';
        }
        message("*", "Markings: %s\n", markings);
    }
    save_pokemon_encrypt(pokemon, &pkm_data);
    return EXIT_SUCCESS;
}
