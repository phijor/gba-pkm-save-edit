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
save_find_section_zero(struct save_block_t* save_block) {
    size_t i = 0;
    while (save_block->sections[i].signature.save_index != 0) {
        i++;
    }
    return i;
}

struct save_unpacked_t*
save_unpack(struct save_file_t* save, size_t index) {
    size_t zero_section_offset =
        save_find_section_zero(&(save->save_blocks[index]));

    struct save_unpacked_t* save_unpacked =
        (struct save_unpacked_t*)malloc(sizeof(save_unpacked));

    if (save_unpacked == NULL) {
        fprintf(stderr,
                E("Could not unpack save structure. Memory allocation failed."));
        return save_unpacked;
    }
    void* current_section_dest = (void*)save_unpacked;
    for (int i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        size_t current_section_id =
            (i + zero_section_offset) % SAVE_SECTIONS_PER_BLOCK;

        struct save_section_t* current_section_source =
            &(save->save_blocks[index].sections[current_section_id]);

        size_t current_section_size =
            save_section_size_by_id[current_section_id]; 
        memcpy(current_section_dest, &(current_section_source->data),
               current_section_size);

        current_section_dest += current_section_size;
    }
    return save_unpacked;
}

int
save_check_section_integrity(struct save_section_t* section) {
    uint32_t checksum = 0;
    size_t dwords_to_read =
        save_section_size_by_id[section->signature.section_id] / sizeof(uint32_t);

    for (size_t i = 0; i < dwords_to_read; i++) {
        checksum += ((uint32_t*) (section->data))[i];
    }
    checksum = ((checksum & 0xffff) + (checksum >> 16)) & 0xffff;

    if (checksum == section->signature.checksum) {
        return EXIT_SUCCESS; 
    }
    else {
        fprintf(stderr,
                "Warning: checksum of section with ID %d\n"
                "         seems to be incorrect:\n"
                "         Checksum present in section:   %X\n"
                "         Checksum calculated from data: %X\n",
                section->signature.section_id,
                section->signature.checksum,
                checksum);
        return EXIT_FAILURE;
    }
}

int
save_check_block_integrity(struct save_block_t* save_block) {
    int exit_status = EXIT_SUCCESS;
    for (size_t i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        struct save_section_t* current_section =
            &(save_block->sections[i]);
        exit_status = save_check_section_integrity(current_section);
    }
    return exit_status;
}

int
save_check_file_integrity(struct save_file_t* save_file) {
    int exit_status = EXIT_SUCCESS;
    for (size_t i = 0; i < SAVE_BLOCKS_PER_FILE; i++) {
        struct save_block_t* current_block =
            &(save_file->save_blocks[i]);
        exit_status = save_check_block_integrity(current_block);

        if (exit_status == EXIT_FAILURE) {
        fprintf(stderr,
                W("One ore more sections in block %ld seem to be corrupted"),
                i);
        }
    }
    return exit_status;
}
