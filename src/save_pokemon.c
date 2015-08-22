#include <stdlib.h>
#include <assert.h>

#include "message.h"
#include "save_pokemon.h"
#include "save_char_encoding.h"

#define arrsize(a) (sizeof(a) / sizeof(a[0]))

const struct save_pokemon_data_permutation_t save_pokemon_data_permutations[] = {
  // G  A  E  M
    {0, 1, 2, 3},
    {0, 1, 3, 2},
    {0, 2, 1, 3},
    {0, 2, 3, 1},
    {0, 3, 1, 2},
    {0, 3, 2, 1},
    {1, 0, 2, 3},
    {1, 0, 3, 2},
    {2, 0, 1, 3},
    {3, 0, 1, 2},
    {2, 0, 3, 1},
    {3, 0, 2, 1},
    {1, 2, 0, 3},
    {1, 3, 0, 2},
    {2, 1, 0, 3},
    {3, 1, 0, 2},
    {2, 3, 0, 1},
    {3, 2, 0, 1},
    {1, 2, 3, 0},
    {1, 3, 2, 0},
    {2, 1, 3, 0},
    {3, 1, 2, 0},
    {2, 3, 1, 0},
    {3, 2, 1, 0},
};

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

void save_pokemon_order_data(struct save_pokemon_boxed_t* pokemon,
                             struct save_pokemon_data_ordered_t* ordered) {
    union save_pokemon_data_t* data = pokemon->data;

    size_t permutation_index =
        pokemon->PID % arrsize(save_pokemon_data_permutations);
    const struct save_pokemon_data_permutation_t* current_permutation =
        &save_pokemon_data_permutations[permutation_index];

    ordered->growth = &data[current_permutation->growth].growth;
    ordered->attacks = &data[current_permutation->attacks].attacks;
    ordered->condition = &data[current_permutation->condition].condition;
    ordered->misc = &data[current_permutation->misc].misc;
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
        message("W+", "Pokémon checksum-mismatch:\n");
        message("",  "Checksum calculated:   %u\n", checksum);
        message("-", "Checksum in save file: %u\n", pokemon->checksum);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

size_t save_pokemon_get_nickname(struct save_pokemon_boxed_t* pokemon, char* nickname) {
    return save_string_decode(nickname, pokemon->nickname, SAVE_POKEMON_NICKNAME_SIZE);
}

size_t save_pokemon_get_ot_name(struct save_pokemon_boxed_t* pokemon, char* OT_name) {
    return save_string_decode(OT_name, pokemon->OT_name, SAVE_POKEMON_OT_NAME_SIZE);
}
