#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <stdlib.h>
#include <stdio.h>

#include "message.h"
#include "editor_dump.h"
#include "save_unpacked.h"

int editor_dump(union save_unpacked_t* save, int argc, char* const* argv) {
    char* dump_file_name = argv[0];

    if (dump_file_name == NULL) {
        message("E", "Missing file name.\n");
        dump_file_name = "dump.sav.unpacked";
    }
    message("I", "Writing to \'%s\'.\n", dump_file_name);

    FILE* dump_file = fopen(dump_file_name, "w");
    fwrite(save, sizeof(union save_unpacked_t), 1, dump_file);
    fclose(dump_file);

    return EXIT_SUCCESS;
}
