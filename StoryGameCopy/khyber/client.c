//
// Created by kkyse on 12/9/2017.
//

#include "client.h"

#include <stdlib.h>
#include <sys/sem.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <sys/shm.h>

#include "story_controller.h"
#include "util/utils.h"

sem_id_t acquire_story_lock(const key_t key) {
    const sem_id_t sem_id = semget(key, 1, 0);
    perror_assert_expr(sem_id != -1);
    struct sembuf args = {.sem_num = 1, .sem_op = -1, .sem_flg = IPC_NOWAIT | SEM_UNDO};
    if (semop(sem_id, &args, 1) == -1) {
        if (errno == EAGAIN) {
            args.sem_flg = SEM_UNDO;
            printf("Story currently in use, waiting for other client to finish.\n");
            perror_assert_expr(semop(sem_id, &args, 1) != -1);
        } else {
            perror_assert_expr(semop);
        }
    }
    return sem_id;
}

void release_story_lock(const sem_id_t sem_id) {
    struct sembuf args = {.sem_num = 1, .sem_op = 1, .sem_flg = SEM_UNDO};
    perror_assert_expr(semop(sem_id, &args, 1) != -1);
}

void read_write_new_line(const key_t key, const char *const filename) {
    const shm_id_t shm_id = shmget(key, sizeof(size_t), 0);
    perror_assert(shm_id != -1, "shmget");
    size_t *line_length_ptr = (size_t *) shmat(shm_id, NULL, 0);
    perror_assert(line_length_ptr, "shmat");
    if (!line_length_ptr) {
        return;
    }
    const size_t line_length = *line_length_ptr;
    
    
    perror_assert_expr(shmdt(line_length_ptr) != -1);
}

int run_story_client(const StoryKey *const story) {
    if (!story_exists(story)) {
        printf("Story doesn't exists yet.  Creating it now.\n");
        run_control_story(CREATE, "./control", story);
    }
    acquire_story_lock(story->semaphore_key);
    read_write_new_line(story->shared_memory_key, story->filename);
    release_story_lock(story->semaphore_key);
}

int main() {
    const StoryKey story_key = {
            .semaphore_key = STORY_SEMAPHORE_KEY,
            .shared_memory_key = STORY_SHARED_MEMORY_KEY,
            .filename = STORY_FILENAME,
    };
    if (run_story_client(&story_key) == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
