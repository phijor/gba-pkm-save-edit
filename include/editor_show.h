#ifndef EDITOR_SHOW_H
#define EDITOR_SHOW_H

#define BIT(x) (1 << x)
#define EDITOR_TRAINER_ID BIT(1)
#define EDITOR_TRAINER_TIME BIT(2)
#define EDITOR_TRAINER_NAME BIT(3)
#define EDITOR_TRAINER_ALL ~0

union save_unpacked_t;
struct save_pokemon_boxed_t;

int editor_show(union save_unpacked_t* save, int argc, char* const* argv);
int editor_show_pokedex(union save_unpacked_t* save, int argc,
                        char* const* argv);
int editor_show_trainer(union save_unpacked_t* save, int argc,
                        char* const* argv);
int editor_show_money(union save_unpacked_t* save, int argc, char* const* argv);

int editor_show_pokemon(union save_unpacked_t* save, int argc,
                        char* const* argv);
int editor_show_pokemon_party(union save_unpacked_t* save, int argc,
                        char* const* argv);
int editor_show_pokemon_box(union save_unpacked_t* save, int argc,
                        char* const* argv);
int editor_show_pokemon_info(struct save_pokemon_boxed_t* pokemon);


#endif
