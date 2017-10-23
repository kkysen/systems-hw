//
// Created by kkyse on 10/16/2017.
//

#include "song_node.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

SongNode *SongNode_new(const Song song, const SongNode *const next) {
    const SongNode local = {.c = &SongNodeClass, .song = song, .next = (SongNode *const) next};
    SongNode *dynamic = (SongNode *) malloc(sizeof(SongNode));
    memcpy(dynamic, &local, sizeof(SongNode));
    return dynamic;
}

SongNode *SongNode_new_sentinel(const Song song) {
    return SongNodeClass.new(song, NULL);
}

size_t SongNode_length(const SongNode *this) {
    size_t i = 0;
    for (; this; ++i, this = this->next);
    return i;
}

SongNode *SongNode_insert_front(const SongNode *const this, const Song song) {
    return SongNodeClass.new(song, this);
}

SongNode *SongNode_insert_in_order(const SongNode *const this, const Song song) {
    if (!this) {
        return NULL; // unnecessary if called as method
    }
    SongNode *prev = NULL;
    for (SongNode *cur = (SongNode *) this; cur; prev = cur, cur = cur->next) {
        if (song.c->compare_to(song, cur->song) < 0) {
            if (!prev) {
                return this->c->insert_front(this, song);
            } else {
                prev->next = cur->c->insert_front(cur, song);
                return (SongNode *) this;
            }
        }
    }
    // insert at end
    prev->next = SongNodeClass.new_sentinel(song);
    return (SongNode *) this;
}

bool SongNode_is_sorted(const SongNode *this) {
    if (!this->next) {
        return true;
    }
    for (const SongNode *cur = this, *next = this->next; next; cur = next, next = next->next) {
        const Song cur_song = cur->song;
        const Song next_song = next->song;
        if (cur_song.c->compare_to(cur_song, next_song) > 0) {
            return false;
        }
    }
    return true;
}

void SongNode_print(const SongNode *this) {
    for (; this; this = this->next) {
        this->song.c->print(this->song);
    }
}

#define find_by_(str_field) \
const SongNode *SongNode_find_by_##str_field(const SongNode *this, const char *const str_field) { \
    for (; this; this = this->next) { \
        if (strcmp(str_field, this->song.str_field) == 0) { \
            return this; \
        } \
    } \
    return NULL; \
}

find_by_(name)

find_by_(artist)

#undef find_by_

const SongNode *SongNode_get(const SongNode *this, const size_t index) {
    for (size_t i = 0; i < index && this; ++i, this = this->next);
    return this;
}

const SongNode *SongNode_get_random_with_length(const SongNode *this, const size_t length) {
    return this->c->get(this, rand() % length);
}

const SongNode *SongNode_get_random(const SongNode *this) {
    return this->c->get_random_with_length(this, this->c->length(this));
}

SongNode *SongNode_remove_front(SongNode *this) {
    SongNode *const next = this->next;
    free(this);
    return next;
}

SongNode *SongNode_remove_song(SongNode *const this, const Song song, size_t *const num_removed) {
    *num_removed = 0;
    for (SongNode *prev = NULL, *cur = this; cur;) {
        if (song.c->equals(song, cur->song)) {
            if (!prev) {
                return this->c->remove_front(this);
            } else {
                prev->next = cur->next;
                song.c->free_other_song_safely(song, cur->song);
//                if (!song.c->is(song, cur->song)) {
//                    cur->song.c->free(cur->song);
//                }
                free(cur);
                ++*num_removed;
                if (!prev->next) {
                    return this;
                }
                cur = prev->next;
            }
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
    return this;
}

SongNode *SongNode_free_nodes_maybe(SongNode *this, const bool free_songs) {
    for (;;) {
        SongNode *const next = this->next;
        if (free_songs) {
            this->song.c->free(this->song);
        }
        free(this);
        if (!next) {
            return NULL;
        }
        this = next;
    }
}

SongNode *SongNode_free_nodes_only(SongNode *const this) {
    return this->c->free_nodes_maybe(this, false);
}

SongNode *SongNode_free(SongNode *const this) {
    return this->c->free_nodes_maybe(this, true);
}

const struct song_node_class SongNodeClass = {
        &SongNode_new,
        &SongNode_new_sentinel,
        &SongNode_length,
        &SongNode_insert_front,
        &SongNode_insert_in_order,
        &SongNode_is_sorted,
        &SongNode_print,
        &SongNode_find_by_name,
        &SongNode_find_by_artist,
        &SongNode_get,
        &SongNode_get_random_with_length,
        &SongNode_get_random,
        &SongNode_remove_front,
        &SongNode_remove_song,
        &SongNode_free_nodes_maybe,
        &SongNode_free_nodes_only,
        &SongNode_free,
};