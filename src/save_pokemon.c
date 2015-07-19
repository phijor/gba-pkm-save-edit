#include <stdlib.h>
#include <assert.h>

#include "save_pokemon.h"

uint32_t save_pokemon_get_crypt_key(struct save_pokemon_boxed_t* pokemon) {
    /* interpret OT's whole ID (public and secret) as one 32-bit number and XOR
     * it with the Pokémons PID to get the de-/encryption key needed to
     * read/edit critical data. */
    return pokemon->PID ^ *((uint32_t*)&pokemon->OT_ID);
}

void save_pokemon_xor_crypt(struct save_pokemon_boxed_t* pokemon) {
    uint32_t key = save_pokemon_get_crypt_key(pokemon);

    assert(sizeof(union save_pokemon_data_t) % sizeof(uint32_t) == 0);
    size_t raw_size = sizeof(union save_pokemon_data_t) / sizeof(uint32_t);

    uint32_t* raw_data = (uint32_t*)pokemon->data;

    for (size_t i = 0; i < raw_size; i++) {
        raw_data[i] ^= key;
    }
}

int save_pokemon_check_data_integrity(struct save_pokemon_boxed_t* pokemon) {
    uint16_t checksum = 0;

    assert(sizeof(union save_pokemon_data_t) % sizeof(uint16_t) == 0);
    size_t raw_size = sizeof(pokemon->data) / sizeof(uint16_t);

    uint16_t* raw_data = (uint16_t*)pokemon->data;

    save_pokemon_xor_crypt(pokemon);
    for (size_t i = 0; i < raw_size; i++) {
        checksum += raw_data[i];
    }
    save_pokemon_xor_crypt(pokemon);

    if (checksum != pokemon->checksum) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
