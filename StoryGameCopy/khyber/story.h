//
// Created by kkyse on 12/9/2017.
//

#ifndef SYSTEMS_STORY_H
#define SYSTEMS_STORY_H

#include <stdbool.h>

#include "util/ipc_utils.h"

#define STORY_SEMAPHORE_KEY 20

#define STORY_SHARED_MEMORY_KEY 21

#define STORY_FILENAME "story.txt"

typedef struct story_key {
    const sem_id_t semaphore_key;
    const shm_id_t shared_memory_key;
    const char *const filename;
} StoryKey;

bool story_exists(const StoryKey *story);

#endif //SYSTEMS_STORY_H
