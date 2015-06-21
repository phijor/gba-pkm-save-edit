#ifndef SAVE_INTEGRITY_H
#define SAVE_INTEGRITY_H

#include <inttypes.h>
#include <stddef.h>

#include "save.h"

uint16_t save_checksum(void* buffer, size_t length);

int save_check_section_validation_code(struct save_section_t* section);
int save_check_section_checksum_integrity(struct save_section_t* section);

int save_check_section_integrity(struct save_section_t* section);
int save_check_block_integrity(struct save_block_t* save_block);
int save_check_file_integrity(struct save_file_t* save_file);

int save_resign_section(struct save_section_t* section);
int save_resign_block(struct save_block_t* block);
int save_resign_file(struct save_file_t* file);

#endif
