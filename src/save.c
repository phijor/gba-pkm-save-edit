#include <stdlib.h>
#include <string.h>

#include "message.h"
#include "save.h"
#include "save_integrity.h"
#include "save_unpacked.h"

#define SAVE_UNPACKED_SIZE 53380

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

size_t save_section_offset_get(struct save_block_t* block) {
    for (size_t i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        if (block->sections[i].signature.section_id == 0) {
            return i;
        }
    }
    return SAVE_SECTIONS_PER_BLOCK;
}

int save_unpack(struct save_block_t* block, union save_unpacked_t* save) {
    size_t zero_section_offset = save_section_offset_get(block);

    if (zero_section_offset >= SAVE_SECTIONS_PER_BLOCK) {
        message("E", "Could not locate first section of block.\n");
        return EXIT_FAILURE;
    }

    char* section_dest = (char*) save;
    for (size_t i = 0; i < SAVE_SECTIONS_PER_BLOCK; i++) {
        size_t section_index = (i + zero_section_offset) % SAVE_SECTIONS_PER_BLOCK;
        struct save_section_t* section_source = &block->sections[section_index];
        size_t section_size = save_section_size_by_id[section_source->signature.section_id];

        memcpy(section_dest, &section_source->data, section_size);

        section_dest += section_size;
    }
    return EXIT_SUCCESS;
}

int save_repack(struct save_block_t* destination,
                union save_unpacked_t* unpacked, uint32_t save_index,
                size_t offset) {
    uint8_t* unpacked_byte_array = (uint8_t*)unpacked;
    size_t byte_offset = 0;

    for (size_t section_id = 0; section_id < SAVE_SECTIONS_PER_BLOCK; section_id++) {
        size_t section_offset = (section_id + offset) % SAVE_SECTIONS_PER_BLOCK;
        struct save_section_t* dest_section =
            &destination->sections[section_offset];
        size_t section_size = save_section_size_by_id[section_id];

        memcpy(dest_section->data, &unpacked_byte_array[byte_offset],
               section_size);
        byte_offset += section_size;

        dest_section->signature.save_index = save_index;
        dest_section->signature.validation_code = SAVE_SECTION_VALIDATION_CODE;
        dest_section->signature.section_id = section_id;
        save_section_resign(dest_section);
    }
    return EXIT_SUCCESS;
}

struct save_block_t* save_most_recent_block_get(struct save_file_t* file) {
    struct save_block_t* most_recent =
        (file->save_blocks[0].sections[0].signature.save_index >
         file->save_blocks[1].sections[0].signature.save_index)
            ? &(file->save_blocks[0])
            : &(file->save_blocks[1]);
    return most_recent;
}

enum save_game_type_t save_gametype_get(union save_unpacked_t* save) {
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
