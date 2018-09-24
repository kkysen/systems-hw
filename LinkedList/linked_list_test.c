//
// Created by kkyse on 10/13/2017.
//

#include "linked_list_test.h"

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void test_range() {
    struct node *list = (struct node *) malloc(sizeof(struct node));
    list->i = -1;
    list->next = NULL;
    int i;
    for (i = 0; i < 1000; ++i) {
        //printf("inserting node %d\n", i);
        list = insert_front(list, i);
    }
    print_list(list);
    free_list(list);
}

void test_fibonacci() {
    struct node *list = (struct node *) malloc(sizeof(struct node));
    list->i = -1;
    list->next = NULL;
    int i;
    int a = 0;
    int b = 1;
    int temp;
    for (i = 0; i < 1000; ++i) {
        //printf("inserting node %d\n", i);
        list = insert_front(list, a);
        temp = a;
        a = b;
        b += temp;
    }
    print_list(list);
    free_list(list);
}

int main() {
    test_range();
    test_fibonacci();
    return 0;
}