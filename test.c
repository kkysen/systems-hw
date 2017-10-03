//
// Created by kkyse on 9/20/2017.
//

#include <stdio.h>
#include <stdlib.h>



int main1() {
    int a[5];
    int j = 97;
    int j_index = 0;
    for (int i = -100; i < 100; ++i) {
        if (a[i] == j) {
            j_index = i;
            printf("a[%d]: %d\n", i, a[i]);
        }
    }
    a[j_index] = 5; // changes j if optimizations are off
    printf("j: %d\n", j);
}

int main2() {
    const char *const s = "hello";
    const char s1[] = "hello";
    printf("s points to: %p\n", (void *) s);
    printf("s1 points to %p\n", (void *) s1);
    printf("address of \"hello\": %p\n", &"hello");
}