//
// Created by kkyse on 12/9/2017.
//

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "util/stacktrace.h"
#include "story_controller.h"
#include "util/utils.h"

int main(const int argc, const char *const *const argv) {
    set_stack_trace_signal_handler();
    
    const char *const program_name = argv[0];
    if (argc <= 1) {
        print_story_usage(program_name);
        return EXIT_SUCCESS;
    }
    
    if (argc > 2) {
        einval(true, "only two arguments are allowed");
    }
    
    const char *const flag_arg = argv[1];
    einval(strlen(flag_arg) != 2, "flag should be 2 chars");
    einval(flag_arg[0] != '-', "flag should begin with '-'");
    const char flag = flag_arg[1];
    
    StoryControlFlag story_flag;
    switch (flag) {
        case 'h':
            story_flag = HELP;
            break;
        case 'c':
            story_flag = CREATE;
            break;
        case 'v':
            story_flag = VIEW;
            break;
        case 'r':
            story_flag = REMOVE;
            break;
        default:
            einval(true, "flag must be either -c, -v, -r, or -h");
    }
    
    const StoryKey story_key = {
            .semaphore_key = STORY_SEMAPHORE_KEY,
            .shared_memory_key = STORY_SHARED_MEMORY_KEY,
            .filename = STORY_FILENAME,
    };
    if (run_control_story(story_flag, program_name, &story_key) == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}