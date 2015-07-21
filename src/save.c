#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "message.h"
#include "save.h"
#include "save_integrity.h"
#include "save_unpacked.h"

size_t save_find_section_zero(struct save_block_t* block) {
    for (size_t i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        if (block->sections[i].signature.section_id == 0) {
            return i;
        }
    }
    return SAVE_SECTIONS_PER_BLOCK;
}

union save_unpacked_t* save_unpack(struct save_block_t* block) {
    size_t zero_section_offset = save_find_section_zero(block);

    if (zero_section_offset >= SAVE_SECTIONS_PER_BLOCK) {
        message("E", "Could not locate first section of block.");
        return NULL;
    }

    union save_unpacked_t* save_unpacked =
        (union save_unpacked_t*)malloc(SAVE_DATA_BYTES_PER_SECTION * SAVE_SECTIONS_PER_BLOCK);

    if (save_unpacked == NULL) {
        message("E",
                "Could not unpack save structure. Memory allocation failed.");
        return NULL;
    }
    void* current_section_dest = (void*)save_unpacked;
    for (size_t i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        size_t current_section_id =
            (i + zero_section_offset) % SAVE_SECTIONS_PER_BLOCK;

        struct save_section_t* current_section_source =
            &(block->sections[current_section_id]);

        memcpy(current_section_dest, &(current_section_source->data),
               SAVE_DATA_BYTES_PER_SECTION);

        current_section_dest += SAVE_DATA_BYTES_PER_SECTION;
    }
    return save_unpacked;
}

int save_repack(struct save_block_t* destination,
                union save_unpacked_t* unpacked, uint32_t save_index,
                size_t offset) {
    uint8_t* unpacked_byte_array = (uint8_t*)unpacked;
    size_t byte_offset = 0;

    for (size_t i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        size_t current_section_offset = (i + offset) % SAVE_SECTIONS_PER_BLOCK;
        struct save_section_t* dest_section =
            &(destination->sections[current_section_offset]);
        memcpy(dest_section->data, &(unpacked_byte_array[byte_offset]),
               SAVE_DATA_BYTES_PER_SECTION);
        byte_offset += SAVE_DATA_BYTES_PER_SECTION;

        dest_section->signature.save_index = save_index;
        dest_section->signature.validation_code = SAVE_SECTION_VALIDATION_CODE;
        dest_section->signature.section_id = i;
        save_resign_section(dest_section);
    }
    return EXIT_SUCCESS;
}

struct save_block_t* save_most_recent_block(struct save_file_t* file) {
    struct save_block_t* most_recent =
        (file->save_blocks[0].sections[0].signature.save_index >
         file->save_blocks[1].sections[0].signature.save_index)
            ? &(file->save_blocks[0])
            : &(file->save_blocks[1]);
    return most_recent;
}

enum save_game_type_t save_get_gametype(union save_unpacked_t* save) {
    /* Assume the game is Ruby/Sapphire. For Firered/Leafgreen the location is
     * the same; Emerald does not have a game_code, instead it's security key
     * is stored at this address.
     */
    switch (save->rusa.game_code) {
        case 0:
            return RUBY_SAPPHIRE;
        case 1:
            return FIRERED_LEAFGREEN;
        default:
            return EMERALD;
    }
    return UNKNOWN;
}
