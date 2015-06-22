#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "save_integrity.h"

uint16_t save_checksum(void* buffer, size_t length) {
    uint32_t checksum = 0;
    uint32_t* dword_buffer = (uint32_t*)buffer;

    assert(length % 4 == 0);
    size_t dwords_to_read = length / sizeof(uint32_t);

    for (size_t i = 0; i < dwords_to_read; i++) {
        checksum += dword_buffer[i];
    }
    return ((checksum & 0xffff) + (checksum >> 16)) & 0xffff;
}

int save_check_section_validation_code(struct save_section_t* section) {
    return (section->signature.validation_code == SAVE_SECTION_VALIDATION_CODE)
               ? EXIT_SUCCESS
               : EXIT_FAILURE;
}

int save_check_section_checksum_integrity(struct save_section_t* section) {
    uint16_t checksum =
        save_checksum(section->data, SAVE_DATA_BYTES_PER_SECTION);

    if (checksum != section->signature.checksum) {
        fprintf(stderr, W("Checksum present in section:   %X\n"
                          "Checksum calculated from data: %X"),
                section->signature.checksum, checksum);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int save_check_section_integrity(struct save_section_t* section) {
    if (save_check_section_checksum_integrity(section) == EXIT_FAILURE) {
        fprintf(stderr,
                W("Checksum of section with ID %d seems to be incorrect"),
                section->signature.section_id);
        return EXIT_FAILURE;
    }

    /* Only the validation code can be wrong at this point, so return wether it
     * is correct or not as a result of this integrity check */
    return save_check_section_validation_code(section);
}

int save_check_block_integrity(struct save_block_t* block) {
    int exit_status = EXIT_SUCCESS;
    for (size_t i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        struct save_section_t* current_section = &(block->sections[i]);

        if (save_check_section_integrity(current_section) == EXIT_FAILURE) {
            exit_status = EXIT_FAILURE;
        }
    }
    return exit_status;
}

int save_check_file_integrity(struct save_file_t* file) {
    int exit_status = EXIT_SUCCESS;

    for (size_t i = 0; i < SAVE_BLOCKS_PER_FILE; i++) {
        struct save_block_t* current_block = &(file->save_blocks[i]);

        if (save_check_block_integrity(current_block) == EXIT_FAILURE) {
            exit_status = EXIT_FAILURE;
            fprintf(
                stderr,
                W("One ore more sections in block %ld seem to be corrupted"),
                i);
        }
    }
    return exit_status;
}

int save_resign_section(struct save_section_t* section) {
    uint16_t checksum =
        save_checksum(section->data, SAVE_DATA_BYTES_PER_SECTION);
    section->signature.checksum = checksum;
    return EXIT_SUCCESS;
}

int save_resign_block(struct save_block_t* block) {
    int exit_status = EXIT_SUCCESS;
    for (size_t i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        struct save_section_t* current_section = &(block->sections[i]);

        if (save_resign_section(current_section) == EXIT_FAILURE) {
            exit_status = EXIT_FAILURE;
        }
    }
    return exit_status;
}

int save_resign_file(struct save_file_t* file) {
    int exit_status = EXIT_SUCCESS;

    for (size_t i = 0; i < SAVE_BLOCKS_PER_FILE; i++) {
        struct save_block_t* current_block = &(file->save_blocks[i]);

        if (save_resign_block(current_block) == EXIT_FAILURE) {
            exit_status = EXIT_FAILURE;
        }
    }
    return exit_status;
}
