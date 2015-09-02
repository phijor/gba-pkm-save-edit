#ifndef SAVE_INTEGRITY_H
#define SAVE_INTEGRITY_H

#include <inttypes.h>
#include <stddef.h>

#include "save.h"

uint16_t save_checksum_get(void* buffer, size_t length);

int save_section_validation_code_check(struct save_section_t* section);
int save_section_data_integrity_check(struct save_section_t* section);

int save_section_integrity_check(struct save_section_t* section);
int save_block_integrity_check(struct save_block_t* save_block);
int save_file_integrity_check(struct save_file_t* save_file);

int save_section_resign(struct save_section_t* section);
int save_block_resign(struct save_block_t* block);
int save_file_resign(struct save_file_t* file);

#endif
