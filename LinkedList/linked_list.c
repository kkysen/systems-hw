//
// Created by kkyse on 10/13/2017.
//

#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

struct node *insert_front(const struct node *const list, const int i) {
    struct node *const front = (struct node *) malloc(sizeof(struct node));
    front->i = i;
    front->next = (struct node *) list;
    return front;
}

struct node *free_list(struct node *list) {
    for (;;) {
        struct node *const next = list->next;
        //printf("freeing node with i = %d\n", list->i);
        free(list);
        if (next == NULL) {
            return NULL;
        }
        list = next;
    }
}

#define MAX_INT_LENGTH 11

char *list_to_string(const struct node *list) {
    size_t length = 16;
    size_t i = 0;
    char *s = (char *) malloc(length * sizeof(char));
    s[i++] = '[';
    for (;; list = list->next) {
        if (length - i < MAX_INT_LENGTH) {
            s = realloc(s, length <<= 1);
        }
        if (list->next == NULL) {
            i += sprintf(s + i, "%d]", list->i);
            break;
        }
        i += sprintf(s + i, "%d, ", list->i);
    }
    s[i] = 0;
    s = realloc(s, i + 1);
    return s;
}

#define SIMPLE_PRINT_LIST false

void print_list(const struct node *list) {
    char *const s = list_to_string(list);
    printf("%s\n", s);
    free(s);
    
    #if (SIMPLE_PRINT_LIST)
    for (;; list = list->next) {
       printf("%d\n", list->i);
       if (list->next == NULL) {
           break;
       }
    }
    #endif
}