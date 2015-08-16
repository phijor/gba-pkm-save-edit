#include <stdlib.h>
#include <stdio.h>

#include "message.h"
#include "editor_export.h"
#include "editor.h"
#include "save_unpacked.h"
#include "save_pokemon_storage.h"

int editor_export(union save_unpacked_t* save, int argc, char* const* argv) {
    const struct editor_command_t commands[] = {
        {.name = "pokemon", .exec = &editor_export_pokemon},
        {.name = NULL, .exec = NULL},
    };
    return editor_call(save, commands, argc, argv);
}

int editor_export_pokemon(union save_unpacked_t* save, int argc,
                          char* const* argv) {
    const struct editor_command_t commands[] = {
        {.name = "team", .exec = &editor_export_pokemon_team},
        {.name = "box", .exec = NULL},
        {.name = NULL, .exec = NULL},
    };
    return editor_call(save, commands, argc, argv);
}

int editor_export_pokemon_team(union save_unpacked_t* save, int argc,
                               char* const* argv) {
    char* dump_file_name = argv[0];

    if (argc < 1 || dump_file_name == NULL) {
        message("E", "Missing file name.\n");
        dump_file_name = "dump.pkm.lst";
    }
    message("I", "Writing to \'%s\'.\n", dump_file_name);
    message("W",
            "This function currently outputs the whole team as one file.\n");

    struct save_pokemon_boxed_t team[6];
    save_pokemon_get_team(save, team);

    FILE* dump_file = fopen(dump_file_name, "w");
    fwrite(team, sizeof(team), 1, dump_file);
    fclose(dump_file);

    return EXIT_SUCCESS;
}
