#include <stdlib.h>
#include <stdio.h>
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
        {.name = "box", .exec = NULL},
        {.name = NULL, .exec = NULL},
    };
    return editor_call(save, commands, argc, argv);
}

int editor_export_pokemon_party(union save_unpacked_t* save, int argc,
                               char* const* argv) {
    struct editor_range_t range = {
        .min = 1, .max = 6,
    };
    if (argc >= 1 && argv[0] != NULL) {
        editor_parse_range(&range, argv[0]);
    } else {
        range.lower = range.min;
        range.upper = range.max;
    }

    long int party_size = save_pokemon_get_party_size(save);
    if (range.upper > party_size) {
        message("W", "Only %ld out of 6 slots are/is occupied.\n", party_size);
        range.upper = party_size;
    }

    message("I", "Exporting Pokemon from party slot(s) %d to %d.\n",
            range.lower, range.upper);

    char export_file_names[6][sizeof("~-[NAME~~~~]-0x[PID~~~]-[OT~~~].g3pkm")] = {'\0'};

    struct save_pokemon_boxed_t party[6];
    save_pokemon_get_party(save, party);

    for (ssize_t i = range.lower; i <= range.upper; i++) {
        struct save_pokemon_boxed_t* current = &party[i - 1];
        char* current_file_name = export_file_names[i - 1];

        if (save_pokemon_slot_is_empty(current)) {
            message("W", "Slot %ld is empty; skipping slot.\n", i);
            continue;
        }

        char nickname[sizeof(((struct save_pokemon_boxed_t*)0)->nickname)];
        save_pokemon_get_nickname(current, nickname);

        char ot_name[sizeof(((struct save_pokemon_boxed_t*)0)->OT_name)];
        save_pokemon_get_ot_name(current, ot_name);

        snprintf(current_file_name, sizeof(export_file_names[0]),
                 "%ld-%s-%#08x-%s.g3pkm", i, nickname, current->PID, ot_name);

        message("I", "Writing slot %ld to \'%s\'.\n", i, current_file_name);
        FILE* export_file = fopen(current_file_name, "w");
        fwrite(current, sizeof(struct save_pokemon_boxed_t), 1, export_file);
        fclose(export_file);
    }

    return EXIT_SUCCESS;
}
