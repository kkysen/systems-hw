//
// Created by kkyse on 10/24/2017.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
    char s1[] = "H";
    // char s2[5]; // static allocation causes bug, too
    char *s2 = (char *) malloc(5 * sizeof(char));
    strncpy(s2, s1, 6);
    printf("%s\n", s2);
}