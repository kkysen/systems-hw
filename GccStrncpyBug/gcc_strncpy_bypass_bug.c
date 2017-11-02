//
// Created by kkyse on 10/24/2017.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(const int argc, const char *const *const argv) {
    size_t x = (.33333333333 * 3.001000000000 > 1) ? 3 : 10;
    size_t len = argc <= 1 ? x : (size_t) strtoul(argv[1], NULL, 10);
    
    printf("\n\n");
    if (len < 6) {
        printf("Still compiles and runs without any errors "
                       "even when the length of dest is less than "
                       "the `n` passed to strncpy.\n"
                       "If the compiler can determine the length "
                       "at compile time, then it will fail.\n"
                       "I think this is a bug in gcc 4.8.4. "
                       "There is no such error using "
                       "the newest version of gcc 7.2.0.\n");
    } else {
        printf("Works as normal when the lengths > `n` passed to strncpy.\n");
    }
    printf("\n\n");
    
    char s1[] = "H";
//    char s2[5];
    char *s2 = (char *) malloc(len * sizeof(char));
    strncpy(s2, s1, 6);
    printf("%s\n", s2);
    
    printf("\n\n");
}