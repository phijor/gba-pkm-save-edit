#ifndef SAVE_H
#define SAVE_H

#include <stddef.h>
#include <inttypes.h>

#include "save_trainer_info.h"

#define W(s) "Warning: "#s"\n"
#define E(s) "Error: "#s"\n"

/* A save file contains 2 blocks, each on a represents a full game state. */
#define SAVE_BLOCKS_PER_FILE 2

/* Each save block is sub-divided into 14 4KB-sections */
#define SAVE_SECTIONS_PER_BLOCK 14

/* The first 0xff4 (4084) bytes of every section represent
 * the save data, the remaining 12B are meta-information
 * (see `save_section_signature) */
#define SAVE_DATA_BYTES_PER_SECTION 0xff4

const size_t save_section_size_by_id[SAVE_SECTIONS_PER_BLOCK];

struct save_section_signature_t {
    uint8_t section_id;
    uint8_t padding;
    uint16_t checksum;
    uint16_t validation_code; // should always be 0x08012025
    uint32_t save_index;
};

struct save_section_t {
    uint8_t data[SAVE_DATA_BYTES_PER_SECTION];
    struct save_section_signature_t signature;
};

struct save_block_t {
    struct save_section_t sections[SAVE_SECTIONS_PER_BLOCK];
};

struct save_file_t {
    struct save_block_t save_blocks[2];
    uint8_t unknown[16384];
};

struct save_unpacked {
    union save_trainer_info_container_t trainer_info;
    // struct save_file_team_items;
    uint8_t save_team_items[3968];
    uint8_t unknown0[3968];
    uint8_t unknown1[3968];
    // struct save_rival_info;
    uint8_t save_rival_info[3848];
    //struct save_pc_buffer pc_buffer;
    uint8_t save_pc_buffer[8*3968 + 2000];
};

size_t 
save_find_section_zero(struct save_block_t* save_block);

struct save_unpacked_t*
save_unpack(struct save_file_t* save, size_t index);

int
save_check_section_integrity(struct save_section_t* section);

int
save_check_block_integrity(struct save_block_t* save_block);

int
save_check_file_integrity(struct save_file_t* save_file);
#endif
