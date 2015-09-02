#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "message.h"
#include "editor_export.h"
#include "editor.h"
#include "editor_parse.h"
#include "save_unpacked.h"
#include "save_pokemon.h"
#include "save_pokemon_storage.h"

int editor_export(union save_unpacked_t* save, int argc, char* const* argv) {
    const struct editor_call_t commands[] = {
        {.name = "pokemon", .exec = &editor_export_pokemon},
        {.name = NULL, .exec = NULL},
    };
    return editor_call(save, commands, argc, argv);
}

int editor_export_pokemon(union save_unpacked_t* save, int argc,
                          char* const* argv) {
    const struct editor_call_t commands[] = {
        {.name = "party", .exec = &editor_export_pokemon_party},
        {.name = "box", .exec = &editor_export_pokemon_box},
        {.name = NULL, .exec = NULL},
    };
    return editor_call(save, commands, argc, argv);
}

int editor_export_pokemon_party(union save_unpacked_t* save, int argc,
                               char* const* argv) {
    int optind = 0;
    struct editor_range_t range = {
        .min = 1, .max = SAVE_PARTY_SLOTS,
    };
    char* directory = NULL;

    if (argc > optind && argv[optind] != NULL) {
        editor_parse_range(&range, argv[optind]);
        optind++;
    } else {
        range.lower = range.min;
        range.upper = range.max;
    }
    if (argc > optind && argv[optind] != NULL) {
        directory = argv[optind];
    } else {
        directory = ".";
    }

    long int party_size = save_pokemon_party_size_get(save);
    if (range.upper > party_size) {
        message("W", "Only %ld out of 6 slots are/is occupied.\n", party_size);
        range.upper = party_size;
    }

    message("I", "Exporting Pokemon from party slot(s) %d to %d.\n",
            range.lower, range.upper);

    struct save_pokemon_boxed_t party[SAVE_PARTY_SLOTS];
    save_pokemon_party_get(save, party);

    for (ssize_t i = range.lower; i <= range.upper; i++) {
        char prefix[2];
        snprintf(prefix, 2, "%1ld", i);
        editor_export_pokemon_write(&party[i - 1], directory, prefix);
    }

    return EXIT_SUCCESS;
}

int editor_export_pokemon_box(union save_unpacked_t* save, int argc,
                               char* const* argv) {
    int optind = 0;
    struct editor_range_t boxes = {
        .min = 1, .max = SAVE_BOXES,
    };
    struct editor_range_t slots = {
        .min = 1, .max = SAVE_BOX_SLOTS,
    };
    char* directory = NULL;

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
    if (argc > optind && argv[optind] != NULL) {
        directory = argv[optind];
    } else {
        directory = ".";
    }

    message("I", "Exporting Pokemon from boxes %d to %d, slots %d to %d each.\n",
            boxes.lower, boxes.upper, slots.lower, slots.upper);

    for (ssize_t box_ind = boxes.lower; box_ind <= boxes.upper; box_ind++) {
        struct save_box_unpacked_t box;
        save_pokemon_box_get(save, box_ind - 1, &box);
        for (ssize_t slot = slots.lower; slot <= slots.upper; slot++) {
            char prefix[6];
            snprintf(prefix, 6, "%02ld-%02ld", box_ind, slot);
            editor_export_pokemon_write(&box.pokemon[slot - 1], directory, prefix);
        }
    }
    return EXIT_SUCCESS;
}

int editor_export_pokemon_write(struct save_pokemon_boxed_t* pokemon,
                                char* dir_path, char* prefix) {
    if (save_pokemon_slot_is_empty(pokemon)) {
        return EXIT_FAILURE;
    }

    size_t file_name_size = strlen(dir_path) + sizeof('/') + strlen(prefix) +
                            sizeof("-[NAME~~~~]-[OT~~~]-0x[PID~~~].g3pkm");
    char* file_name = calloc(file_name_size, sizeof(char));

    char nickname[SAVE_POKEMON_NICKNAME_SIZE];
    save_pokemon_nickname_get(pokemon, nickname);

    char ot_name[SAVE_TRAINER_NAME_SIZE];
    save_pokemon_ot_name_get(pokemon, ot_name);

    snprintf(file_name, file_name_size, "%s/%s-%s-%s-%#08x.g3pkm",
             dir_path, prefix, nickname, ot_name, pokemon->PID);

    message("I", "Writing Pokemon to \'%s\'.\n", file_name);
    FILE* export_file = fopen(file_name, "w");
    fwrite(pokemon, sizeof(struct save_pokemon_boxed_t), 1, export_file);
    fclose(export_file);
    free(file_name);
    return EXIT_SUCCESS;
}
