//
// Created by kkyse on 10/4/2017.
//

#include "string_tests.h"

#include <stdio.h>

#include <string.h>

#include "string_funcs.h"

size_t strnlen(const char *s, size_t n); // for some reason gcc can't find strnlen header

void test_strlen() {
    printf("\n\nTesting strlen\n\n");
    
    printf("\"Hello\" has %zu characters. Should be %zu\n", my_strlen("Hello"), strlen("Hello"));
    printf("\"\" has %zu characters. Should be %zu\n", my_strlen(""), strlen(""));
}

void test_strnlen() {
    printf("\n\nTesting strnlen\n\n");
    
    const char *const message = "\"Hello\" has %zu characters up to %u. Should be %zu\n";
    printf(message, my_strnlen("Hello", 5), 5, strnlen("Hello", 5));
    printf(message, my_strnlen("Hello", 6), 6, strnlen("Hello", 6));
    printf(message, my_strnlen("Hello", 70000), 70000, strnlen("Hello", 70000));
    printf(message, my_strnlen("Hello", 4), 4, strnlen("Hello", 4));
    printf("\"\" has %zu characters up to 1. Should be %zu\n", my_strnlen("", 1), strnlen("", 1));
}

void test_strcpy() {
    printf("\n\nTesting strcpy\n\n");
    
    char strcpy1[] = "Hello";
    char strcpy2[5];
    char strcpy3[6];
    my_strcpy(strcpy2, strcpy1);
    my_strcpy(strcpy3, strcpy2);
    printf("strcpy1: %s \nstrcpy2: %s\nstrcpy3: %s\n", strcpy1, strcpy2, strcpy3);
    char strcpy4[] = "Hello";
    char strcpy5[6];
    char strcpy6[6];
    strcpy(strcpy5, strcpy4);
    strcpy(strcpy6, strcpy5);
    printf("Should be...\n");
    printf("strcpy1: %s \nstrcpy2: %s\nstrcpy3: %s\n", strcpy4, strcpy5, strcpy6);
}

void test_strncpy() {
    printf("\n\nTesting strncpy\n\n");
    
    char strncpy1[] = "Hello";
    char strncpy2[5];
    char strncpy3[3 + 1];
    strncpy3[3] = 0;
    my_strncpy(strncpy2, strncpy1, 6);
    my_strncpy(strncpy3, strncpy2, 3);
    printf("strncpy1: %s \nstrncpy2: %s\nstrncpy3: %s\n", strncpy1, strncpy2, strncpy3);
    char strncpy4[] = "Hello";
    char strncpy5[6];
    char strncpy6[3 + 1];
    strncpy6[3] = 0;
    strncpy(strncpy5, strncpy4, 6);
    strncpy(strncpy6, strncpy5, 3);
    printf("Should be...\n");
    printf("strncpy1: %s \nstrncpy2: %s\nstrncpy3: %s\n", strncpy4, strncpy5, strncpy6);
}

void test_strcat() {
    printf("\n\nTesting strcat\n\n");
    
    char strcat1[20];
    char strcat2[20];
    strcat1[0] = 0;
    strcat2[0] = 0;
    strcpy(strcat1, " there!");
    strcpy(strcat2, "Hello");
    char strcat3[50];
    strcat3[0] = 0;
    my_strcat(strcat2, strcat1);
    my_strcat(strcat3, strcat2);
    printf("strcat1: %s \nstrcat2: %s\nstrcat3: %s\n", strcat1, strcat2, strcat3);
    char strcat4[20];
    char strcat5[20];
    strcat4[0] = 0;
    strcat5[0] = 0;
    strcpy(strcat4, " there!");
    strcpy(strcat5, "Hello");
    char strcat6[50];
    strcat6[0] = 0;
    strcat(strcat5, strcat4);
    strcat(strcat6, strcat5);
    printf("Should be...\n");
    printf("strcat1: %s \nstrcat2: %s\nstrcat3: %s\n", strcat4, strcat5, strcat6);
}

void test_strncat() {
    printf("\n\nTesting strncat\n\n");
    
    char strncat1[20];
    char strncat2[20];
    strncat1[0] = 0;
    strncat2[0] = 0;
    strcpy(strncat1, " there!");
    strcpy(strncat2, "Hello");
    char strncat3[50];
    strncat3[0] = 0;
    my_strncat(strncat2, strncat1, 4);
    my_strncat(strncat3, strncat2, 7);
    printf("strncat1: %s \nstrncat2: %s\nstrncat3: %s\n", strncat1, strncat2, strncat3);
    char strncat4[20];
    char strncat5[20];
    strncat4[0] = 0;
    strncat5[0] = 0;
    strcpy(strncat4, " there!");
    strcpy(strncat5, "Hello");
    char strncat6[50];
    strncat6[0] = 0;
    strncat(strncat5, strncat4, 4);
    strncat(strncat6, strncat5, 7);
    printf("Should be...\n");
    printf("strncat1: %s \nstrncat2: %s\nstrncat3: %s\n", strncat4, strncat5, strncat6);
}

void test_strcmp() {
    printf("\n\nTesting strcmp\n\n");
    
    printf("hello vs. hi: %d, should be %d\n", my_strcmp("hello", "hi"), strcmp("hello", "hi"));
    printf("orange vs. apple: %d, should be %d\n", my_strcmp("orange", "apple"), strcmp("orange", "apple"));
}

void test_strncmp() {
    printf("\n\nTesting strncmp\n\n");
    
    // TODO
}

void test_strchr() {
    printf("\n\nTesting strchr\n\n");
    
    printf("l is at position %p of hello, should be %p\n", (void *) my_strchr("hello", 'l'), (void *) strchr("hello", 'l'));
    printf("h is at position %p of hello, should be %p\n", (void *) my_strchr("hello", 'h'), (void *) strchr("hello", 'h'));
}

void test_strstr() {
    printf("\n\nTesting strstr\n\n");
    
    // TODO
}

int main() {
    printf("\n\nTesting String Functions\n\n");
    
    test_strlen();
    test_strnlen();
    test_strcpy();
    test_strncpy();
    test_strcat();
    test_strncat();
    test_strcmp();
    test_strncmp();
    test_strchr();
    test_strstr();
    
    return 0;
}


















