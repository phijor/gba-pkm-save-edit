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

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "save_integrity.h"
#include "save.h"

#define arrsize(arr) (sizeof(arr)/sizeof(arr[0]))

// int main(int argc, char* const* argv) {
int main() {
    FILE* input = stdin;
    FILE* output = stdout;
    struct save_file_t save;
    fread(&save, sizeof(save), 1, input);
    if (save_check_file_integrity(&save) == EXIT_FAILURE) {
        fprintf(stderr, E("Save file seems to be corrupt."));
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, I("Save file passed integrity-test."));
    union save_unpacked_t* unpacked = save_unpack(&(save.save_blocks[0]));
    // fwrite(unpacked, sizeof(union save_unpacked_t), 1, output);
    fprintf(output,
            "Money: %0u\n"
            "First item in PC: %u\n"
            "Quantity: %u\n",
            unpacked->rusa.money, unpacked->rusa.items.pc_storage[0].index,
            unpacked->rusa.items.pc_storage[0].quantity);
    for (size_t i = 0;
         i < arrsize(unpacked->rusa.items.ball_pocket);
         i++) {
        fprintf(output, "Ball %lu: %ux, ID%u\n", i,
                unpacked->rusa.items.ball_pocket[i].quantity,
                unpacked->rusa.items.ball_pocket[i].index);
    }
    return EXIT_SUCCESS;
}
