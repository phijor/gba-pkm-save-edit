#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "save.h"

int main(int argc, char* const* argv) {
    FILE* input = stdin;
    FILE* output = stdout;
    struct save_file_t save;
    fread(&save, sizeof(save), 1, input);
    // ptrdiff_t sid_offset = (void*)&(save.A.sections[0].signature.section_id) -
    //                        (void*)&(save.A.sections[0]);
    // fprintf(output, "%ld", sid_offset);
    if (save_check_file_integrity(&save) == EXIT_FAILURE) {
        fprintf(output,
                W("Save file seems to be corrupt."));
    }
    else {
        fprintf(output,
                "Save file passed integrity-test.\n");
    }
    return EXIT_SUCCESS;
}
