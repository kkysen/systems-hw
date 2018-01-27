//
// Created by kkyse on 12/9/2017.
//

#ifndef SYSTEMS_IO_UTILS_H
#define SYSTEMS_IO_UTILS_H

#include <fcntl.h>

#include "resource_utils.h"

#define O_CREATE_EXCL (O_CREAT | O_EXCL | USER_RW)

typedef int fd_t;

off_t get_file_size(const char *filename);

void check_file_exists(fd_t fd, const char *filename);

#endif //SYSTEMS_IO_UTILS_H
