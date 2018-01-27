//
// Created by kkyse on 12/9/2017.
//

#ifndef SYSTEMS_IPC_UTILS_H
#define SYSTEMS_IPC_UTILS_H

#include <sys/types.h>
#include <sys/ipc.h>

#include "resource_utils.h"

typedef int sem_id_t;
typedef int shm_id_t;

#define IPC_CREATE_EXCL (IPC_CREAT | IPC_EXCL | USER_RW)

sem_id_t create_semaphore(key_t key, int initial_value);

int remove_semaphore(key_t key);

shm_id_t create_shared_memory(key_t key, size_t size);

int remove_shared_memory(key_t key);

void check_semaphore_exists(sem_id_t sem_id, key_t key);

void check_shared_memory_exists(shm_id_t shm_id, key_t key);

#endif //SYSTEMS_IPC_UTILS_H
