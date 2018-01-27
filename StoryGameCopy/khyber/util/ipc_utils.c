//
// Created by kkyse on 12/9/2017.
//

#include "ipc_utils.h"

#include <sys/sem.h>
#include <sys/shm.h>

#include "utils.h"

sem_id_t create_semaphore(const key_t key, const int initial_value) {
    const sem_id_t sem_id = semget(key, 1, IPC_CREATE_EXCL);
    if (sem_id == -1) {
        // EEXIST is somewhat expected
        if (errno != EEXIST) {
            perror("semget");
        }
        return -1;
    }
    // undefined union w/ cmd "enum" simulates templated function
    if (semctl(sem_id, 0, SETVAL, initial_value) == -1) {
        perror("semctl SETVAL");
        return -1;
    }
    return sem_id;
}

int remove_semaphore(const key_t key) {
    const sem_id_t sem_id = semget(key, 1, 0);
    if (sem_id == -1) {
        if (errno != ENOENT) {
            perror("semget");
        }
        return -1;
    }
    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("semctl");
        return -1;
    }
    return 0;
}

shm_id_t create_shared_memory(const key_t key, const size_t size) {
    const shm_id_t shm_id = shmget(key, size, IPC_CREATE_EXCL);
    if (shm_id == -1) {
        if (errno != EEXIST) {
            perror("shmget");
        }
        return -1;
    }
    return shm_id;
}

int remove_shared_memory(const key_t key) {
    // TODO check 0 size argument
    const shm_id_t shm_id = shmget(key, 0, 0);
    if (shm_id == -1) {
        if (errno != ENOENT) {
            perror("shmget");
        }
        return -1;
    }
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        return -1;
    }
    return 0;
}

static void check_key_exists(const int id, const key_t key, const char *const ipc_structure_name) {
    if (check_eexists(id)) {
        printf("The %s with the key %zu already exists.\n", ipc_structure_name, key);
    }
}

void check_semaphore_exists(const sem_id_t sem_id, const key_t key) {
    check_key_exists(sem_id, key, "semaphore");
}

void check_shared_memory_exists(const shm_id_t shm_id, const key_t key) {
    check_key_exists(shm_id, key, "shared memory segment");
}