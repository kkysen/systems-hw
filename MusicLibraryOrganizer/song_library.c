//
// Created by kkyse on 10/16/2017.
//

#include <sys/types.h>

#include "song_library.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

// TODO implement methods

#define membersize(type, member) (sizeof(((type *)0)->member))

#define arraylen(array) (sizeof(array) / sizeof(*(array)))

const char *DEFAULT_SONGS_CSV = "songs.csv";

SongLibrary *SongLibrary_new() {
    const SongLibrary local = {.c = &SongLibraryClass};
    SongLibrary *dynamic = (SongLibrary *) malloc(sizeof(struct song_library));
    memcpy(dynamic, &local, sizeof(struct song_library));
    return dynamic;
}

const SongNode *SongLibrary_all_songs(const SongLibrary *const this) {
    // put songs in a temp array first, because linked list uses reverse order
    const Song **const songs = (const Song **) malloc(this->num_songs * sizeof(Song *));
    for (size_t row = 0, i = 0; row < arraylen(this->table); ++row) {
        for (const SongNode *head = this->table[row]; head; head = head->next, ++i) {
            songs[i] = &head->song;
        }
    }
    // add to SongNode linked list in reverse order, because using insert_front()
    const SongNode *all_songs = NULL;
    for (int i = (int) this->num_songs - 1; i >= 0; --i) {
        all_songs = SongNodeClass.insert_front(all_songs, *songs[i]);
    }
    free(songs);
    return all_songs;
}

SongNode *SongLibrary_songs_by_artist_letter(const SongLibrary *const this, const char letter) {
    return this->table[(unsigned char) letter];
}

void SongLibrary_add_song(SongLibrary *const this, const Song song) {
    const size_t i = (unsigned char) *song.artist;
//    printf("i: %zu\n", i);
    SongNode **const row_ptr = this->table + i;
    SongNode *const row = *row_ptr;
    if (!row) {
//        printf("adding song to new linked list\n");
        *row_ptr = SongNodeClass.new_sentinel(song);
    } else {
//        printf("adding song to existing linked list\n");
        *row_ptr = row->c->insert_in_order(row, song); // insert and update head in table
//        printf("%p\n", (*row_ptr)->c);
//        (*row_ptr)->c->print(*row_ptr);
    }
    this->lengths[i]++;
    this->num_songs++;
}

// needed b/c header not on school computers for some reason
// #include <sys/types.h> // done at top of file
ssize_t getline(char **lineptr, size_t *n, FILE *stream); // NOLINT

static inline void _make_LF(char *const line, const size_t length) {
    // stupid carriage return mess up everything
    if (line[length - 1] == '\r') {
        // getline() or other functions will probably fail if no '\n' at all anyways
        line[length - 1] = '\n'; // fix CR on old OS X
    }
    if (line[length - 2] == '\r') {
        line[length - 2] = 0; // fix CRLF on Windows
    }
}

int SongLibrary_add_songs_from_csv(SongLibrary *const this, const char *const filename) {
    FILE *const file = fopen(filename, "r");
    if (!file) {
        return -1;
    }
    for (size_t length = 0;;) {
        char *line = NULL;
        if (getline(&line, &length, file) < 0) {
            free(line);
            break;
        }
        _make_LF(line, length);
        const char *name = strtok(line, ",");
        const char *artist = strtok(NULL, "\n");
//        printf("_____________________\n");
//        printf("line: %s\n", line);
//        printf("adding song: %s by %s\n", name, artist);
//        printf("_____________________\n");
        this->c->add_song(this, SongClass.new(name, artist));
        free(line);
    }
    fclose(file);
    return EXIT_SUCCESS;
}

int SongLibrary_add_songs_from_default_csv(SongLibrary *const this) {
    return this->c->add_songs_from_csv(this, DEFAULT_SONGS_CSV);
}

const SongNode *SongLibrary_find_by_artist(const SongLibrary *const this, const char *const artist) {
    assert(artist);
    const SongNode *const row = this->c->songs_by_artist_letter(this, *artist);
    if (!row) {
        return NULL;
    }
    return row->c->find_by_artist(row, artist);
}

const SongNode *SongLibrary_find_by_name(const SongLibrary *const this, const char *const name) {
    assert(name);
    for (size_t i = 0; i < arraylen(this->table); ++i) {
        const SongNode *const row = this->table[i];
        const SongNode *const found = row->c->find_by_name(row, name);
        if (found) {
            return found;
        }
    }
    return NULL;
}

const SongNode *SongLibrary_find_song(const SongLibrary *const this, const Song song) {
    const SongNode *songs_by_artist = this->c->find_by_artist(this, song.artist);
    return songs_by_artist->c->find_by_name(songs_by_artist, song.name);
}

void SongLibrary_print_by_letter(const SongLibrary *const this, const char letter) {
    const SongNode *const row = this->c->songs_by_artist_letter(this, letter);
    if (row) {
        row->c->print(row);
    }
}

void SongLibrary_print_by_artist(const SongLibrary *const this, const char *const artist) {
    const SongNode *cur = this->c->find_by_artist(this, artist);
    // alphabetized, so this is allowed (stopping when given artist isn't the current song anymore)
    for (; cur; cur = cur->next) {
        if (strcmp(artist, cur->song.artist) != 0) {
            break;
        }
        cur->song.c->print(cur->song);
    }
}

void SongLibrary_print(const SongLibrary *const this) {
//    for (size_t i = 0; i * 8 < sizeof(this->table); ++i) {
//        printf("%zu: %zu\n", i, ((size_t *) this->table)[i]);
//    }
    for (size_t i = 0; i < arraylen(this->table); ++i) {
        const SongNode *const row = this->table[i];
        if (row) {
//            printf("printing row %zu\n", i);
            row->c->print(row);
        }
    }
}

void SongLibrary_shuffle_and_print(const SongLibrary *const this, const size_t num_songs) {
    for (size_t i = 0; i < num_songs; ++i) {
        size_t rand_index = rand() % this->num_songs;
        for (size_t j = 0; j < arraylen(this->lengths); ++j) {
            const size_t index = this->lengths[j];
            if (rand_index < index) {
                const SongNode *const row = this->table[j];
                Song song = row->c->get(row, rand_index)->song;
                song.c->print(song);
                break;
            }
            rand_index -= index;
        }
    }
}

void SongLibrary_remove_song(SongLibrary *const this, const Song song) {
    const size_t i = (unsigned char) *song.artist;
    SongNode **const row_ptr = this->table + i;
    SongNode *const row = *row_ptr;
    if (!row) {
        return; // song not in library
    }
    size_t num_removed;
    *row_ptr = row->c->remove_song(row, song, &num_removed);
    this->lengths[i] -= num_removed;
    this->num_songs -= num_removed;
}

void SongLibrary_remove_all_songs(SongLibrary *const this) {
    for (size_t i = 0; i < arraylen(this->table); ++i) {
        SongNode *const row = this->table[i];
        if (row) {
            row->c->free(row);
        }
    }
    memset(this->table, 0, sizeof(this->table));
    memset(this->lengths, 0, sizeof(this->lengths));
    this->num_songs = 0;
}

void SongLibrary_free(SongLibrary *const this) {
    this->c->remove_all_songs(this);
    free(this);
}

const struct song_library_class SongLibraryClass = {
        &SongLibrary_new,
        &SongLibrary_all_songs,
        &SongLibrary_songs_by_artist_letter,
        &SongLibrary_add_song,
        &SongLibrary_add_songs_from_csv,
        &SongLibrary_add_songs_from_default_csv,
        &SongLibrary_find_by_artist,
        &SongLibrary_find_by_name,
        &SongLibrary_find_song,
        &SongLibrary_print_by_letter,
        &SongLibrary_print_by_artist,
        &SongLibrary_print,
        &SongLibrary_shuffle_and_print,
        &SongLibrary_remove_song,
        &SongLibrary_remove_all_songs,
        &SongLibrary_free,
};