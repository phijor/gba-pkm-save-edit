#ifndef SAVE_H
#define SAVE_H

#include <stddef.h>
#include <inttypes.h>

#include "save_ruby_sapphire.h"
#include "save_emerald.h"
#include "save_firered_leafgreen.h"

#define I(s) "Info: " s "\n"
#define W(s) "Warning: " s "\n"
#define E(s) "Error: " s "\n"

/* A save file contains 2 blocks, each on a represents a full game state. */
#define SAVE_BLOCKS_PER_FILE 2

/* Each save block is sub-divided into 14 4KB-sections */
#define SAVE_SECTIONS_PER_BLOCK 14

/* The first 0xff4 (4084) bytes of every section represent
 * the save data, the remaining 12B are meta-information
 * (see `save_section_signature) */
#define SAVE_DATA_BYTES_PER_SECTION 0xff4

/* Each section contains a validation code */
#define SAVE_SECTION_VALIDATION_CODE 0x08012025

#define SAVE_UNPACKED_TOTAL 55552

const size_t save_section_size_by_id[SAVE_SECTIONS_PER_BLOCK];

struct save_section_signature_t {
    uint8_t section_id;
    uint8_t padding;
    uint16_t checksum;
    uint32_t validation_code;  // should always be 0x08012025
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

union save_unpacked_t {
    struct save_ruby_sapphire_t rusa;
    struct save_emerald_t emer;
    struct save_firered_leafgreen_t frlg;
};

size_t save_find_section_zero(struct save_block_t* save_block);
union save_unpacked_t* save_unpack(struct save_block_t* block);
int save_repack(struct save_block_t* destination,
                union save_unpacked_t* unpacked, uint32_t save_index);
#endif
