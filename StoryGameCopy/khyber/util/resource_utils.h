//
// Created by kkyse on 12/9/2017.
//

#ifndef SYSTEMS_RESOURCE_UTILS_H
#define SYSTEMS_RESOURCE_UTILS_H

#include <stdbool.h>
#include <fcntl.h>

#define USER_RW (S_IRUSR | S_IWUSR)

bool check_error(int error, int id);

bool check_eexists(int id);

bool check_enoent(int id);

#endif //SYSTEMS_RESOURCE_UTILS_H
