//
// Created by kkyse on 10/4/2017.
//

#ifndef STRINGS_STRING_FUNCS_H
#define STRINGS_STRING_FUNCS_H

#include <stdlib.h>

size_t my_strlen(const char *const s);

size_t my_strnlen(const char *const s, size_t length);

char *my_strcpy(char *dest, const char *src);

char *my_strncpy(char *dest, const char *src, size_t length);

char *my_strcat(char *dest, const char *src);

char *my_strncat(char *dest, const char *src, size_t length);

int my_strcmp(const char *s1, const char *s2);

int my_strncmp(const char *s1, const char *s2, size_t length);

char *my_strchr(const char *s, const int c);

char *my_strstr(const char *s1, const char *s2);

#endif //STRINGS_STRING_FUNCS_H
