//
// Created by kkyse on 10/4/2017.
//

#include <string.h>
#include <stdio.h>
#include "string_funcs.h"

size_t my_strlen(const char *const s) {
    const char *p = s - 1;
    while (*++p);
    return p - s;
}

size_t my_strnlen(const char *const s, size_t length) {
    const char *p = s - 1;
    length += 2;
    while (--length && *++p);
    return p - s;
}

char *my_strcpy(char *dest, const char *src) {
    char *tmp = dest;
    while ((*dest++ = *src++));
    return tmp;
}

char *my_strncpy(char *dest, const char *src, size_t length) {
    char *tmp = dest;
    while (length-- && (*dest++ = *src++));
    if (length > 0) {
        memset(dest, 0, length + 1);
    }
    return tmp;
}

char *my_strcat(char *dest, const char *src) {
    char *tmp = dest;
    while (*dest++);
    dest--;
    while ((*dest++ = *src++));
    return tmp;
}

char *my_strncat(char *dest, const char *src, size_t length) {
    char *tmp = dest;
    while (*dest++);
    dest--;
    while (length-- && (*dest++ = *src++));
    if (length > 0) {
        *dest = 0; // add null terminator
    }
    return tmp;
}

int my_strcmp(const char *s1, const char *s2) {
    char c1 = 0;
    char c2 = 0;
    while ((c1 = *s1++) && (c2 = *s2++) && c1 == c2);
    return c1 - c2;
}

int my_strncmp(const char *s1, const char *s2, size_t length) {
    char c1 = 0;
    char c2 = 0;
    while (length-- && (c1 = *s1++) && (c2 = *s2++) && c1 == c2);
    return c1 - c2;
}

char *my_strchr(const char *s, const int c) {
    if (c == 0) {
        return (char *) s + my_strlen(s);
    }
    char temp;
    while ((temp = *s++) && temp != c);
    if (temp == c) {
        return (char *) s - 1;
    }
    return NULL;
}

char *my_strstr(const char *s1, const char *s2) {
    printf("my_strstr is not implemented yet\n");
    return strstr(s1, s2);
//    for (int i = 0; s1[i]; s1++) {
//
//    }
//    return (char *) s1; // FIXME
}

/*
 * These functions implement DW's headers
 * by simply wrapping the above my_ prefixed functions,
 * which implement the same headers in string.h.
 */

int mystrlen(char *s) {
    return (int) my_strlen(s);
}

int mystrnlen(char *s, int n) {
    return (int) my_strnlen(s, (size_t) n);
}

char *mystrcpy(char *dest, char *source) {
    return my_strcpy(dest, source);
}

char *mystrncpy(char *dest, char *source, int n) {
    return my_strncpy(dest, source, (size_t) n);
}

char *mystrcat(char *dest, char *source) {
    return my_strcat(dest, source);
}

char *mystrncat(char *dest, char *source, int n) {
    return my_strncat(dest, source, (size_t) n);
}

int mystrcmp(char *s1, char *s2) {
    return my_strcmp(s1, s2);
}

char *mystrchr(char *s1, char c) {
    return my_strchr(s1, c);
}

char *mystrstr(char *s1, char *s2) {
    return my_strstr(s1, s2);
}