//
// Created by kkyse on 10/5/2017.
//

#include "io.h"

#include <stdlib.h>
#include <string.h>
#import <unistd.h>

#define SAFE_IO_MODIFICATIONS true

const char *HOME = NULL;
size_t HOME_LEN = 0;

const char *get_home() {
    if (HOME == NULL) {
        HOME = getenv("HOME");
        HOME_LEN = strlen(HOME);
    }
    return HOME;
}

const size_t get_home_len() {
    get_home();
    return HOME_LEN;
}

bool is_sudo() {
    return system("sudo -v") == 0;
}

static inline bool contains(const char *const string, const char *const substring) {
    return strstr(string, substring) != NULL;
}

bool is_dangerous_filename(const char *const filename) {
    return contains(filename, "khyber")
           || contains(filename, "sen")
           || contains(filename, "kkyse")
           || is_sudo();
}

char *checked_filename(const char *const filename) {
    if (!is_dangerous_filename(filename)) {
        return (char *) filename;
    }
    #if (SAFE_IO_MODIFICATIONS)
    return NULL;
    #endif
    const size_t len = strlen(filename);
    char *const new_filename = (char *) malloc((len + 2) * sizeof(char)); // for ~ and null
    strcpy(new_filename, filename);
    new_filename[len] = '~';
    new_filename[len + 1] = 0;
    return new_filename;
}

char filename_buffer[FILENAME_MAX];

char *new_strcat(const char *const s1, const char *const s2) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    char *const s3 = (char *) malloc((len1 + len2 + 1) * sizeof(char));
    strcpy(s3, s1);
    strcpy(s3 + len1, s2);
    return s3;
}

char *filename_cat(const char *const s1, const char *const s2) {
    
}

int modify_file(const char *const filename, int (*const modifier)(const FILE *const in, const FILE *const out)) {
    FILE *const in = fopen(filename, "r");
    if (in == NULL) {
        return -1;
    }
    
    const char *const tmp_filename = new_strcat(filename, "~");
    FILE *const out = fopen(tmp_filename, "w");
    if (out == NULL) {
        fclose(in);
        return -1;
    }
    
    int ret = modifier(in, out);
    if (fclose(in) != 0) {
        fclose(out);
        return -1;
    };
    if (fclose(out) != 0) {
        return -1;
    }
    
    unlink(filename);
    rename(tmp_filename, filename);
    
    free((char *) tmp_filename);
    
    
    
    return ret;
}
