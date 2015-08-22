/* gba-pkm-save-edit -- A commandline application to edit save files of
 *                      Pokémon-games for the GBA
 * Copyright (C) <2015>  <Philipp Joram>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

#include <stdlib.h>
#include <getopt.h>

#include "save_integrity.h"
#include "editor.h"
#include "message.h"

int main(int argc, char* const* argv) {
    char current_option;
    while ((current_option = getopt(argc, argv, "h")) != -1) {
    }

    char* save_file_name = NULL;
    if (optind >= argc || argv[optind] == NULL) {
        message("E", "No input file specified. Exiting.\n");
        exit(EXIT_FAILURE);
    }
    save_file_name = argv[optind++];
    message("I", "Reading from \'%s\'.\n", save_file_name);

    FILE* save_file = fopen(save_file_name, "r");
    if (save_file == NULL) {
        message("E", "Unable to open '%s'. Exiting.\n", save_file_name);
        exit(EXIT_FAILURE);
    }

    struct save_file_t save;
    fread(&save, sizeof(save), 1, save_file);
    fclose(save_file);

    if (save_check_file_integrity(&save) == EXIT_FAILURE) {
        message("E", "Save file seems to be corrupt.\n");
        exit(EXIT_FAILURE);
    }
    message("I", "Save file passed integrity-test.\n");

    struct save_block_t* most_recent = save_most_recent_block(&save);
    union save_unpacked_t* unpacked = save_unpack(most_recent);

    int editor_argc = argc - optind;
    char* const* editor_argv = (editor_argc > 0) ? &argv[optind] : NULL;
    int ret = editor(unpacked, editor_argc, editor_argv);
    free(unpacked);

    return ret;
}
