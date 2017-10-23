//
// Created by kkyse on 10/16/2017.
//

#ifndef SYSTEMS_SONG_H
#define SYSTEMS_SONG_H

#include <stdbool.h>

extern const char *PRE_SONG_STRING;

struct song {
    
    const struct song_class *const c;
    
    const char *const name;
    const char *const artist;
    
} typedef Song;

struct song_class {
    
    Song (*const new)(const char *const name, const char *const artist);
    
    bool (*const is)(const Song this, const Song song);
    
    bool (*const equals)(const Song this, const Song song);
    
    int (*const compare_to)(const Song this, const Song song);
    
    char *(*const to_string)(const Song this);
    
    void (*const print)(const Song this);
    
    void (*const free)(const Song this);
    
    void (*const free_other_song_safely)(const Song this, const Song song);
    
};

extern const struct song_class SongClass;

#endif //SYSTEMS_SONG_H
