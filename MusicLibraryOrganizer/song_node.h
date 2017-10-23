//
// Created by kkyse on 10/16/2017.
//

#ifndef SYSTEMS_SONG_NODE_H
#define SYSTEMS_SONG_NODE_H

#include <stddef.h>

#include "song.h"

typedef struct song_node {
    
    const struct song_node_class *const c;
    Song song;
    struct song_node *next;
    
} SongNode;

struct song_node_class {
    
    SongNode *(*const new)(const Song song, const SongNode *const next);
    
    SongNode *(*const new_sentinel)(const Song song);
    
    size_t (*const length)(const SongNode *this);
    
    SongNode *(*const insert_front)(const SongNode *const this, const Song song);
    
    SongNode *(*const insert_in_order)(const SongNode *this, const Song song);
    
    bool (*const is_sorted)(const SongNode *this);
    
    void (*const print)(const SongNode *this);
    
    const SongNode *(*const find_by_name)(const SongNode *this, const char *const name);
    
    const SongNode *(*const find_by_artist)(const SongNode *this, const char *const artist);
    
    const SongNode *(*const get)(const SongNode *this, const size_t index);
    
    const SongNode *(*const get_random_with_length)(const SongNode *this, const size_t length);
    
    const SongNode *(*const get_random)(const SongNode *this);
    
    SongNode *(*const remove_front)(SongNode *this);
    
    SongNode *(*const remove_song)(SongNode *const this, const struct song, size_t *const num_removed);
    
    SongNode *(*const free_nodes_maybe)(SongNode *this, const bool free_songs);
    
    SongNode *(*const free_nodes_only)(SongNode *const this);
    
    SongNode *(*const free)(SongNode *const this);
    
};

extern const struct song_node_class SongNodeClass;

#endif //SYSTEMS_SONG_NODE_H
