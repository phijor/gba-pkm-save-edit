#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdlib.h>
#include <stdio.h>

#include "editor_show.h"
#include "editor.h"
#include "save_pokedex.h"

int editor_show(union save_unpacked_t* save, int argc, char* const* argv) {
    const struct editor_command_t commands[] = {
        {.name = "pokedex", .exec = &editor_show_pokedex},
        {.name = NULL, .exec = NULL},
    };
    return editor_call(save, commands, argc, argv);
}

int editor_show_pokedex(union save_unpacked_t* save, int argc,
                        char* const* argv) {
    const char* status_string[] = {
            [UNSEEN] = "Unseen",    [SEEN] = "Seen",      [OWNED] = "Caught",
            [POKEDEX_SUCCESS] = "", [POKEDEX_ERROR] = "",
    };

    for (size_t i = 0; i < SAVE_DEX_SIZE; i++) {
        enum save_pokedex_status_t status = save_get_pokedex_entry(save, i);
        if (status == POKEDEX_ERROR) {
            return EXIT_FAILURE;
        }
        fprintf(stdout, "#%03lu: %s\n", i, status_string[status]);
    }
    return EXIT_SUCCESS;
}
