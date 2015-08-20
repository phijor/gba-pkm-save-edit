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
        {.name = "team", .exec = &editor_export_pokemon_team},
        {.name = "box", .exec = NULL},
        {.name = NULL, .exec = NULL},
    };
    return editor_call(save, commands, argc, argv);
}

int editor_export_pokemon_team(union save_unpacked_t* save, int argc,
                               char* const* argv) {
    struct editor_range_t range = {
        .min = 0, .max = 5,
    };
    if (argc >= 1 && argv[0] != NULL) {
        editor_parse_range(&range, argv[0]);
    } else {
        range.lower = range.min;
        range.upper = range.max;
    }
    message("I", "Exporting Pokemon from team slot(s) %d to %d.\n",
            range.lower + 1, range.upper + 1);

    char export_file_names[6][sizeof("~-[NAME~~~~]-0x[PID~~~]-[OT~~~].pkm")] = {'\0'};

    struct save_pokemon_boxed_t team[6];
    save_pokemon_get_team(save, team);

    for (ssize_t i = range.lower; i <= range.upper; i++) {
        struct save_pokemon_boxed_t* current = &team[i];

        if (save_pokemon_slot_is_empty(current)) {
            message("I", "Slot %ld is empty; skipping slot.\n", i + 1);
            continue;
        }

        char nickname[sizeof(((struct save_pokemon_boxed_t*)0)->nickname)];
        save_pokemon_get_nickname(current, nickname);

        char ot_name[sizeof(((struct save_pokemon_boxed_t*)0)->OT_name)];
        save_pokemon_get_ot_name(current, ot_name);

        snprintf(export_file_names[i], sizeof(export_file_names[0]),
                 "%ld-%s-%#08x-%s.pkm", i + 1, nickname, current->PID, ot_name);

        message("I", "Writing to %s\n", export_file_names[i]);
        FILE* export_file = fopen(export_file_names[i], "w");
        fwrite(current, sizeof(struct save_pokemon_boxed_t), 1, export_file);
        fclose(export_file);
    }

    return EXIT_SUCCESS;
}
