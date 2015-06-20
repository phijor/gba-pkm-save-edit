#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "save.h"

const size_t save_section_size_by_id[] = {
    3884,  // Trainer info
    3968,  // Team / items
    3968,  // Unknown
    3968,  // Unknown
    3848,  // Rival info
    3968,  // PC buffer A
    3968,  // PC buffer B
    3968,  // PC buffer C
    3968,  // PC buffer D
    3968,  // PC buffer E
    3968,  // PC buffer F
    3968,  // PC buffer G
    3968,  // PC buffer H
    2000   // PC buffer I
};

size_t
save_find_section_zero(struct save_block_t* block) {
    for (size_t i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        if (block->sections[i].signature.section_id == 0) {
            return i;
        }
    }
    return SAVE_SECTIONS_PER_BLOCK;
}

union save_unpacked_t*
save_unpack(struct save_block_t* block) {
    size_t zero_section_offset =
        save_find_section_zero(block);

    if (zero_section_offset >= SAVE_SECTIONS_PER_BLOCK) {
        fprintf(stderr,
                E("Could not locate first section of block"));
        return NULL;
    }

    union save_unpacked_t* save_unpacked =
        (union save_unpacked_t*)malloc(sizeof(save_unpacked));

    if (save_unpacked == NULL) {
        fprintf(stderr,
                E("Could not unpack save structure. Memory allocation failed."));
        return NULL;
    }
    void* current_section_dest = (void*)save_unpacked;
    for (int i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        size_t current_section_id =
            (i + zero_section_offset) % SAVE_SECTIONS_PER_BLOCK;

        struct save_section_t* current_section_source =
            &(block->sections[current_section_id]);

        size_t current_section_size =
            save_section_size_by_id[current_section_id]; 
        memcpy(current_section_dest, &(current_section_source->data),
               current_section_size);

        current_section_dest += current_section_size;
    }
    return save_unpacked;
}
