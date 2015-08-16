#ifndef EDITOR_EXPORT_H
#define EDITOR_EXPORT_H

union save_unpacked_t;

int editor_export(union save_unpacked_t* save, int argc, char* const* argv);

int editor_export_pokemon(union save_unpacked_t* save, int argc,
                          char* const* argv);

int editor_export_pokemon_team(union save_unpacked_t* save, int argc,
                               char* const* argv);

#endif /* ----- #ifndef EDITOR_EXPORT_H ----- */
