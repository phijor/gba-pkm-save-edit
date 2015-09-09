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
#include <ctype.h>
#include <getopt.h>

#include "editor.h"
#include "message.h"

int main(int argc, char* const* argv) {
    struct editor_options_t options = {
        .o_output_file = NULL,
        .i_input_file = NULL,
        .progname = argv[0],
        .h_show_help = 0,
    };

    opterr = 0;
    char current_option;
    while ((current_option = getopt(argc, argv, "hi:o:")) != -1) {
        switch (current_option) {
            case 'h':
                options.h_show_help = 1;
                break;
            case 'i':
                options.i_input_file = optarg;
                break;
            case 'o':
                options.o_output_file = optarg;
                break;
            case '?':
                switch (optopt) {
                    case 'i':
                    case 'o':
                        message("E", "Option '-%c' requires an argument.\n",
                                optopt);
                        break;
                    default:
                        if (isprint(optopt)) {
                            message("E", "Unknown option '-%c'.\n", optopt);
                        } else {
                            message("E", "Unknown option character '\\x%x'.\n",
                                    optopt);
                        }
                }
                return EXIT_FAILURE;
        }
    }

    int editor_argc = argc - optind;
    char* const* editor_argv = (editor_argc > 0) ? &argv[optind] : NULL;

    return editor(&options, editor_argc, editor_argv);
}
