//
// Created by kkyse on 10/13/2017.
//

#ifndef SYSTEMS_LINKED_LIST_H
#define SYSTEMS_LINKED_LIST_H

struct node {
    int i;
    struct node *next;
};

struct node *insert_front(const struct node *const list, const int i);

struct node *free_list(struct node *list);

char *list_to_string(const struct node *list);

void print_list(const struct node *const list);

#endif //SYSTEMS_LINKED_LIST_H
