#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdlib.h>
#include <stdio.h>

#include "message.h"
#include "editor_show.h"
#include "editor.h"
#include "save_common.h"
#include "save_pokedex.h"
#include "save_trainer.h"

int editor_show(union save_unpacked_t* save, int argc, char* const* argv) {
    const struct editor_command_t commands[] = {
        {.name = "pokedex", .exec = &editor_show_pokedex},
        {.name = "trainer", .exec = &editor_show_trainer},
        {.name = "money",   .exec = &editor_show_money},
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
        message("", "#%03lu: %s\n", i, status_string[status]);
    }
    return EXIT_SUCCESS;
}

int editor_show_trainer(union save_unpacked_t* save, int argc,
                        char* const* argv) {
    uint32_t info_flags = EDITOR_TRAINER_ALL;
    if (info_flags & EDITOR_TRAINER_ID) {
        struct save_trainer_id_t id;
        save_get_trainer_id(&id, save);
        message("",
                "TID: %u\n"
                "SID: %u\n",
                id.TID, id.SID);
    }
    if (info_flags & EDITOR_TRAINER_TIME) {
        struct save_time_played_t time;
        save_get_time_played(&time, save);
        message("",
                "Time played: %02u:%02u:%02u/%02u\n",
                time.hours,
                time.minutes,
                time.seconds,
                time.frames);
    }
    if (info_flags & EDITOR_TRAINER_NAME) {
        char name[8] = {'\0'};
        save_get_name(name, save);
        message("", "Name: %s\n", name);
    }
    return EXIT_SUCCESS;
}

int editor_show_money(union save_unpacked_t* save, int argc,
                      char* const* argv) {
    message("", "Money: %u Poké$\n", save_get_money(save));
    return EXIT_SUCCESS;
}
