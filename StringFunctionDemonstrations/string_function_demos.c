//
// Created by kkyse on 9/28/2017.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

/*
 * strchr is like indexOf(char) in Java.
 * It accepts a const char * (null-terminated string)
 * and an int-promoted char to search for.
 * It returns a char * to the first occurrence of the character in the string.
 * The null character is included in the search.
 * If the character was not found, the NULL pointer is returned.
 */
size_t strchr_index(const char *const string, const int search_char) {
    return strchr(string, search_char) - string;
}

/*
 * strstr is like indexOf(String) in Java
 * It accepts two const char *,
 * the first one being the main string
 * and the second being the substring being searched for.
 * It returns a char * to the first occurrence of str2 in str1.
 * The null character is not included in the search.
 * If str2 is not found in str1, the NULL pointer is returned.
 */
size_t strstr_index(const char *const string, const char *const substring) {
    return strstr(string, substring) - string;
}

int main() {
    assert(strchr_index("Hello, World", ',') == 5);
    assert(strstr_index("Khyber Sen", "r S") == 5);
    
    perror(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}