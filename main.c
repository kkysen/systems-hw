//
// Created by kkyse on 9/9/2017.
//

#include <stdio.h>

int main1() {
    
    printf("Hello, World\n");
    
    typedef int (*F)();
    F f = &main1;
    F *p = &f;
    (*p)();
    
    return 0;
}