//
// Created by kkyse on 10/16/2017.
//

#include "song.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

const char *PRE_SONG_STRING = "";

static inline char *new_strcpy(const char *const s) {
    char *const copy = (char *) malloc((strlen(s) + 1) * sizeof(char));
    strcpy(copy, s);
//    printf("%s\n", s);
    return copy;
}

Song Song_new(const char *const name, const char *const artist) {
    assert(name);
    assert(artist);
    assert(*name);
    assert(*artist);
    return (Song) {.c = &SongClass, .name = new_strcpy(name), .artist = new_strcpy(artist)};
}

bool Song_is(const Song this, const Song song) {
    return this.artist == song.artist && this.name == song.name;
}

bool Song_equals(const Song this, const Song song) {
    #if (MAIN_DEBUG)
    printf("comparing:\n");
    this.c->print(this);
    song.c->print(song);
    printf("\n");
    #endif
    return this.c->compare_to(this, song) == 0;
}

int Song_compare_to(const Song this, const Song song) {
    const int cmp = strcmp(this.artist, song.artist);
    if (cmp != 0) {
        return cmp;
    }
    return strcmp(this.name, song.name);
}

char *Song_to_string(const Song this) {
//    printf("to_stringing song\n");
    const size_t new_length = strlen(this.name) + strlen("[ by ]") + strlen(this.artist) + 100;
    char *const s = (char *) malloc((new_length + 1) * sizeof(char));
    sprintf(s, "[%s by %s]", this.name, this.artist);
//    printf("to_stringed song\n");
    return s;
}

void Song_print(const Song this) {
//    printf("printing song\n");
    char *const s = this.c->to_string(this);
    printf("%s", PRE_SONG_STRING);
    printf("%s\n", s);
    free(s);
//    printf("printed song\n");
}

#define free_field(field) free((char *) this.field); *((char **) &this.field) = NULL

void Song_free(const Song this) {
    // set to NULL to prevent double free(); shouldn't happen, but being safe
    free_field(artist);
    free_field(name);
}

#undef free_field

#define free_other_songs_field(field) if (this.field != song.field) \
    free((char *) song.field), *((char **) &song.field) = NULL

void Song_free_other_song_safely(const Song this, const Song song) {
    free_other_songs_field(artist);
    free_other_songs_field(name);
}

#undef free_other_songs_field

const struct song_class SongClass = {
        &Song_new,
        &Song_is,
        &Song_equals,
        &Song_compare_to,
        &Song_to_string,
        &Song_print,
        &Song_free,
        &Song_free_other_song_safely,
};