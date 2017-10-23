//
// Created by kkyse on 10/5/2017.
//

#ifndef STRINGS_IO_H
#define STRINGS_IO_H

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

extern const char *HOME;

extern size_t HOME_LEN;

const char *get_home();

const size_t get_home_len();

bool is_sudo();

bool is_dangerous_filename(const char *const filename);

char *checked_filename(const char *const filename);

#endif //STRINGS_IO_H
