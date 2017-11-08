//
// Created by kkyse on 11/1/2017.
//

#include <stdint.h>
#include <sys/types.h>
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

char file_perms_str[10 + 1] = {0};

#define bit(n, i) (((n) >> (i)) & 1)

void one_file_perm(const mode_t mode, const uint8_t index) {
    file_perms_str[index + 0] = (char) (bit(mode, 2) ? 'r' : '-');
    file_perms_str[index + 1] = (char) (bit(mode, 1) ? 'w' : '-');
    file_perms_str[index + 2] = (char) (bit(mode, 0) ? 'x' : '-');
}

const char *file_perms(const mode_t mode) {
//    for (int i = sizeof(mode) * 8 - 1; i >= 0; i--) {
//        printf("%d, ", bit(mode, i));
//    }
    file_perms_str[0] = (char) (bit(mode, 15) ? '-' : 'd');
    one_file_perm(mode >> 0, 7);
    one_file_perm(mode >> 3, 4);
    one_file_perm(mode >> 6, 1);
    return file_perms_str;
}

int print_file_stats(const char *const path) {
    struct stat stats;
    if (stat(path, &stats) == -1) {
        perror("stat");
        return -1;
    }
    const mode_t mode = stats.st_mode;
    const off_t file_size = stats.st_size;
    const time_t access_time = stats.st_atime;
    printf("%s %zd %s\n", file_perms(mode), file_size, ctime(&access_time));
    return 0;
}

int main(const int argc, const char *const *const argv) {
    printf("\n\nPrinting file stats about this executable (%s)\n", argv[0]);
    if (print_file_stats(argv[0]) == -1) {
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}