//
// Created by kkyse on 12/9/2017.
//

#include "io_utils.h"

#include <stdio.h>

#include "resource_utils.h"

off_t get_file_size(const char *const filename) {
    struct stat stats;
    stat(filename, &stats);
    return stats.st_size;
}

void check_file_exists(const fd_t fd, const char *const filename) {
    if (check_eexists(fd)) {
        printf("The file \"%s\" already exists.\n", filename);
    }
}