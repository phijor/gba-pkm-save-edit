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
#include "save_unpacked.h"
#include "editor.h"
#include "message.h"

int main(int argc, char* const* argv) {
    char current_option;
    while ((current_option = getopt(argc, argv, "h")) != -1) {
    }

    int editor_argc = argc - optind;
    char* const* editor_argv = (editor_argc > 0) ? &argv[optind] : NULL;

    return editor(editor_argc, editor_argv);
}
