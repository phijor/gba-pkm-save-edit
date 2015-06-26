#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdlib.h>
#include <stdio.h>

#include "editor_dump.h"
#include "save_unpacked.h"

int editor_dump(union save_unpacked_t* save, int argc, char* const* argv) {
    fprintf(stderr, "Writing to \"%s\".", argv[0]);
    FILE* dump_file = fopen(argv[0], "w");
    fwrite(save, sizeof(union save_unpacked_t), 1, dump_file);
    fclose(dump_file);
    return EXIT_SUCCESS;
}
