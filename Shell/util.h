//
// Created by kkyse on 11/9/2017.
//

#ifndef SYSTEMS_UTIL_H
#define SYSTEMS_UTIL_H

#include <sys/types.h>

typedef unsigned int uint;

#define arraylen(array) (sizeof((array)) / sizeof(*(array)))

char *copy_str(const char *s);

#endif //SYSTEMS_UTIL_H
