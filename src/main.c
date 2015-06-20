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
