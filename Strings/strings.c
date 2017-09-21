

#include <stdio.h>
#include <stdlib.h>

size_t strlen(const char *const s) {
    const char *p = s;
    while (*p++);
    return p - 1 - s;
}

size_t strnlen(const char *const s, size_t length) {
    const char *p = s;
    ++length;
    while (length-- && *p++);
    return p - 1 - s;
}

char *strcpy(char *dest, const char *src) {
    char *tmp = dest;
    while ((*dest++ = *src++));
    return tmp;
}

char *strncpy(char *dest, const char *src, size_t length) {
    char *tmp = dest;
    while (length-- && (*dest++ = *src++));
    return tmp;
}

char *strcat(char *dest, const char *src) {
    char *tmp = dest;
    while (*dest++);
    while ((*dest++ = *src++));
    return tmp;
}

char *strncat(char *dest, const char *src, size_t length) {
    char *tmp = dest;
    while (*dest++);
    while (length-- && (*dest++ = *src++));
    return tmp;
}

int main() {
    printf("%zu\n", strlen("Hello"));
    printf("%zu\n", strnlen("Hello", 3));
    printf("%zu\n", strnlen("Hello", 10));
    
    char *s = (char *) malloc(1000);
    strcpy(s, "Hello");
    printf("%s\n", s);
    
    strncpy(s, "Hello, World", 6);
    printf("%s\n", s);
    
    strncpy(s, "Hello, World", 20);
    printf("%s\n", s);
    
}