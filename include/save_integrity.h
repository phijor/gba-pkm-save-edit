#ifndef SAVE_INTEGRITY_H
#define SAVE_INTEGRITY_H

#include "save.h"

int
save_check_section_integrity(struct save_section_t* section);

int
save_check_block_integrity(struct save_block_t* save_block);

int
save_check_file_integrity(struct save_file_t* save_file);
#endif
