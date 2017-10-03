//
// Created by kkyse on 9/21/2017.
//

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

#define LENGTH 10

void print_array(const int *const a, const size_t length, const char *const name) {
    for (size_t i = 0; i < length; ++i) {
        printf("%s[%zu] = %d\n", name, i, a[i]);
    }
}

int main() {
    srand((unsigned int) time(NULL));
    
    int a[LENGTH];
    int i;
    for (i = 0; i < LENGTH - 1; ++i) {
        a[i] = rand();
    }
    a[LENGTH - 1] = 0;
    
    for (i = 0; i < LENGTH; ++i) {
        printf("a[%d] = %d\n", i, a[i]);
    }
    printf("\n");
    
    int b[LENGTH];
    int *c = a - 1;
    int *d = b + LENGTH;
    while (d != b) {
        *--d = *++c;
    }
    
    print_array(b, LENGTH, "b");
    
    return 0;
}