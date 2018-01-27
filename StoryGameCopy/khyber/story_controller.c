//
// Created by kkyse on 12/9/2017.
//

#include "story_controller.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/shm.h>

#include "util/stacktrace.h"
#include "util/utils.h"
#include "util/io_utils.h"
#include "util/ipc_utils.h"

static void create_story_semaphore(const key_t key) {
    const int initial_value = 1;
    const sem_id_t sem_id = create_semaphore(key, 1);
    check_semaphore_exists(sem_id, key);
    printf("Created a semaphore w/ key = %zu and an initial value of %d.\n", key, initial_value);
}

static void create_story_shared_memory(const key_t key) {
    const size_t size = sizeof(size_t);
    const shm_id_t shm_id = create_shared_memory(key, size);
    check_shared_memory_exists(shm_id, key);
    
    // set line length in shared memory to 0
    size_t *line_length = (size_t *) shmat(shm_id, NULL, 0);
    perror_assert(line_length, "shmat");
    do {
        if (!line_length) {
            _Static_assert(false);
        }
    } while (false);
    *line_length = 0;
    perror_assert_expr(shmdt(line_length) != -1);
    
    printf("Created a shared memory segment w/ key = %zu and a size of %zu.\n", key, size);
}

static void create_story_file(const char *const filename) {
    const fd_t fd = open(filename, O_CREATE_EXCL);
    check_file_exists(fd, filename);
    printf("Created a story file named \"%s\".\n", filename);
}

void create_story(const StoryKey *const story) {
    create_story_semaphore(story->semaphore_key);
    create_story_shared_memory(story->shared_memory_key);
    create_story_file(story->filename);
}

void view_story(const StoryKey *const story) {
    const char *const filename = story->filename;
    const fd_t fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }
    const off_t signed_file_size = get_file_size(filename);
    if (signed_file_size < -1) {
        perror("get_file_size");
        return;
    }
    const size_t file_size = (size_t) signed_file_size;
    char *const buffer = (char *) malloc(file_size + sizeof(char));
    if (!buffer) {
        perror("malloc");
        assert(buffer);
    }
    buffer[file_size] = 0;
    if (read(fd, buffer, file_size) == -1) {
        perror("read");
        return;
    }
    printf("%s\n", buffer);
}

static int remove_story_semaphore(const key_t key) {
    assert(remove_semaphore(key) != -1);
    printf("Removed the semaphore w/ key = %zu.\n", key);
    return 0;
}

static int remove_story_shared_memory(const key_t key) {
    assert(remove_shared_memory(key) != -1);
    printf("Removed the shared memory w/ key = %zu.\n", key);
    return 0;
}

static int remove_story_file(const char *const filename) {
    perror_assert_expr(remove(filename) != -1);
    return 0;
}

void remove_story(const StoryKey *const story) {
    if (!story_exists(story)) {
        printf("Couldn't remove story because it (or some part of it) doesn't exists.\n");
    }
    remove_story_semaphore(story->semaphore_key);
    remove_story_shared_memory(story->shared_memory_key);
    remove_story_file(story->filename);
}

void print_story_usage(const char *const program_name) {
    printf("Usage: %s -flag:\n"
                   "    where -flag = \n"
                   "        -c: setup a new story\n"
                   "        -v: view the story\n"
                   "        -r: remove the story\n"
                   "        -h: display this help message\n",
           program_name);
}

int run_control_story(StoryControlFlag flag, const char *program_name, const StoryKey *const story) {
    switch (flag) {
        case HELP: {
            print_story_usage(program_name);
            break;
        }
        case CREATE: {
            create_story(story);
            break;
        }
        case VIEW: {
            view_story(story);
            break;
        }
        case REMOVE: {
            remove_story(story);
            break;
        }
    }
    return 0;
}