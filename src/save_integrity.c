#include <stdlib.h>
#include <assert.h>

#include "message.h"
#include "save_integrity.h"

uint16_t save_checksum_get(void* buffer, size_t length) {
    uint32_t checksum = 0;
    uint32_t* dword_buffer = (uint32_t*)buffer;

    assert(length % 4 == 0);
    size_t dwords_to_read = length / sizeof(uint32_t);

    for (size_t i = 0; i < dwords_to_read; i++) {
        checksum += dword_buffer[i];
    }
    return ((checksum & 0xffff) + (checksum >> 16)) & 0xffff;
}

int save_section_validation_code_check(struct save_section_t* section) {
    return (section->signature.validation_code == SAVE_SECTION_VALIDATION_CODE)
               ? EXIT_SUCCESS
               : EXIT_FAILURE;
}

int save_section_data_integrity_check(struct save_section_t* section) {
    size_t section_size =
        save_section_size_by_id[section->signature.section_id];
    uint16_t checksum = save_checksum_get(section->data, section_size);

    if (checksum != section->signature.checksum) {
        message("W+", "Checksum of section with ID %u seems to be incorrect\n",
                section->signature.section_id);
        message(" ", "Checksum present in section:   %X\n",
                section->signature.checksum);
        message("-", "Checksum calculated from data: %X\n", checksum);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int save_section_integrity_check(struct save_section_t* section) {
    if (save_section_data_integrity_check(section) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    /* Only the validation code can be wrong at this point, so return wether it
     * is correct or not as a result of this integrity check */
    return save_section_validation_code_check(section);
}

int save_block_integrity_check(struct save_block_t* block) {
    int exit_status = EXIT_SUCCESS;
    for (size_t i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        struct save_section_t* current_section = &(block->sections[i]);

        if (save_section_integrity_check(current_section) == EXIT_FAILURE) {
            exit_status = EXIT_FAILURE;
        }
    }
    return exit_status;
}

int save_file_integrity_check(struct save_file_t* file) {
    int exit_status = EXIT_SUCCESS;

    for (size_t i = 0; i < SAVE_BLOCKS_PER_FILE; i++) {
        struct save_block_t* current_block = &(file->save_blocks[i]);

        if (save_block_integrity_check(current_block) == EXIT_FAILURE) {
            exit_status = EXIT_FAILURE;
            message("W",
                    "One ore more sections in block %ld seem to be corrupted\n",
                    i);
        }
    }
    return exit_status;
}

int save_section_resign(struct save_section_t* section) {
    uint16_t checksum = save_checksum_get(
        section->data, save_section_size_by_id[section->signature.section_id]);
    section->signature.checksum = checksum;
    return EXIT_SUCCESS;
}

int save_block_resign(struct save_block_t* block) {
    int exit_status = EXIT_SUCCESS;
    for (size_t i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        struct save_section_t* current_section = &(block->sections[i]);

        if (save_section_resign(current_section) == EXIT_FAILURE) {
            exit_status = EXIT_FAILURE;
        }
    }
    return exit_status;
}

int save_file_resign(struct save_file_t* file) {
    int exit_status = EXIT_SUCCESS;

    for (size_t i = 0; i < SAVE_BLOCKS_PER_FILE; i++) {
        struct save_block_t* current_block = &(file->save_blocks[i]);

        if (save_block_resign(current_block) == EXIT_FAILURE) {
            exit_status = EXIT_FAILURE;
        }
    }
    return exit_status;
}
