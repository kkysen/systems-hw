//
// Created by kkyse on 10/16/2017.
//

#ifndef SYSTEMS_SONG_LIBRARY_H
#define SYSTEMS_SONG_LIBRARY_H

#include "song_node.h"

#define SONG_TABLE_LENGTH 1 << (8 * sizeof(char))

extern const char *DEFAULT_SONGS_CSV;

typedef struct song_library {
    
    const struct song_library_class *const c;
    SongNode *table[SONG_TABLE_LENGTH]; // 256
    size_t lengths[SONG_TABLE_LENGTH];
    size_t num_songs;
    
} SongLibrary;

struct song_library_class {
    
    SongLibrary *(*const new)();
    
    const SongNode *(*const all_songs)(const SongLibrary *const this);
    
    SongNode *(*const songs_by_artist_letter)(const SongLibrary *const this, const char letter);
    
    void (*const add_song)(SongLibrary *const this, const Song song);
    
    int (*const add_songs_from_csv)(SongLibrary *const this, const char *const filename);
    
    int (*const add_songs_from_default_csv)(SongLibrary *const this);
    
    const SongNode *(*const find_by_artist)(const SongLibrary *const this, const char *const artist);
    
    const SongNode *(*const find_by_name)(const SongLibrary *const this, const char *const name);
    
    const SongNode *(*const find_song)(const SongLibrary *const this, const Song song);
    
    void (*const print_by_letter)(const SongLibrary *const this, const char letter);
    
    void (*const print_by_artist)(const SongLibrary *const this, const char *const artist);
    
    void (*const print)(const SongLibrary *const this);
    
    void (*const shuffle_and_print)(const SongLibrary *const this, const size_t num_songs);
    
    void (*const remove_song)(SongLibrary *const this, const Song song);
    
    void (*const remove_all_songs)(SongLibrary *const this);
    
    void (*const free)(SongLibrary *const this);
    
};

extern const struct song_library_class SongLibraryClass;

#endif //SYSTEMS_SONG_LIBRARY_H
