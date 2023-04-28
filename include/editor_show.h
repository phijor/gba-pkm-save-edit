#ifndef EDITOR_SHOW_H
#define EDITOR_SHOW_H

union save_unpacked_t;
struct save_pokemon_t;

int editor_show(union save_unpacked_t* save, int argc, char* const* argv);
int editor_show_pokedex(union save_unpacked_t* save, int argc,
                        char* const* argv);
int editor_show_trainer(union save_unpacked_t* save, int argc,
                        char* const* argv);
int editor_show_map(union save_unpacked_t* save, int argc,
                        char* const* argv);
int editor_show_pokemon(union save_unpacked_t* save, int argc,
                        char* const* argv);
int editor_show_pokemon_party(union save_unpacked_t* save, int argc,
                        char* const* argv);
int editor_show_pokemon_box(union save_unpacked_t* save, int argc,
                        char* const* argv);
int editor_show_pokemon_info(struct save_pokemon_t* pokemon);


#endif
