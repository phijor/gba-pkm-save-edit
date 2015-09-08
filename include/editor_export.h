#ifndef EDITOR_EXPORT_H
#define EDITOR_EXPORT_H

union save_unpacked_t;
struct save_pokemon_t;

int editor_export(union save_unpacked_t* save, int argc, char* const* argv);

int editor_export_pokemon(union save_unpacked_t* save, int argc,
                          char* const* argv);

int editor_export_pokemon_party(union save_unpacked_t* save, int argc,
                               char* const* argv);

int editor_export_pokemon_box(union save_unpacked_t* save, int argc,
                               char* const* argv);

int editor_export_pokemon_write(struct save_pokemon_t* pokemon,
                                char* dir_path, char* prefix);

#endif /* ----- #ifndef EDITOR_EXPORT_H ----- */
