//
// Created by kkyse on 12/9/2017.
//

#ifndef SYSTEMS_CONTROL_H
#define SYSTEMS_CONTROL_H

#include <sys/types.h>

#include "story.h"

void create_story(const StoryKey *story);

void view_story(const StoryKey *story);

void remove_story(const StoryKey *story);

void print_story_usage(const char *program_name);

typedef enum story_control_flag {
    CREATE,
    VIEW,
    REMOVE,
    HELP,
} StoryControlFlag;

int run_control_story(StoryControlFlag flag, const char *program_name, const StoryKey *story);

#endif //SYSTEMS_CONTROL_H
