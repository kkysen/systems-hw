#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stacktrace.h"

#define randrange(start, end) (rand() % ((end) - (start)) + (start))

int8_t fork_recurse(const uint32_t fork_count) {
    if (fork_count == 0) {
        return 0;
    }
    const pid_t parent_pid = getpid();
    printf("Parent forking (PID = %d)...\n", parent_pid);
    const pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        printf("Fork failed\n");
        return -1;
    } else if (pid == 0) {
        const pid_t child_pid = getpid();
        
        // need to seed each process or else rand() will be same
        //srand(fork_count + ((unsigned int) time(NULL) ^ (child_pid << 16)));
        // when you seed based on PID, rand() still returns very similar values
        
        // or can call rand() variable number of times
        for (uint32_t i = 0; i < fork_count; ++i) {
            rand();
        }
        
        const uint8_t seconds = (uint8_t) randrange(5, 20);
        printf("Child PID: %d, sleeping for %u seconds\n", child_pid, seconds);
        sleep(seconds);
        printf("Finished (PID = %d)\n", child_pid);
        exit(seconds);
    } else {
        fork_recurse(fork_count - 1);
        int status;
        const pid_t child_pid = wait(&status);
        printf("status: %x\n", status);
        if (child_pid == -1 || !WIFEXITED(status)) {
            perror("wait");
            printf("Wait failed. Something probably went wrong with child process\n");
            return -1;
        }
        const uint8_t seconds = (uint8_t) WEXITSTATUS(status);
        printf("Child process finished (PID = %d), slept for %u seconds\n", child_pid, seconds);
        printf("Parent done (PID = %d)\n", parent_pid);
        
        // I'm assuming "Print a message that the parent is done and then end the program"
        // means I should exit the program here and kill the other child,
        // not just return and let the other child finish, too.
        exit(EXIT_SUCCESS);
    }
}

int once() {
    printf("Before forking...\n");
    pid_t pid = fork();
    if (pid == 0) {
        printf("Child PID: %d\n", pid);
        int randtime = rand() % 1 + 5;
        printf("randtime: %d\n", randtime);
        sleep(randtime);
        printf("Finished!\n");
        return randtime;
    } else if (pid < 0) {
        exit(1);
    } else {
        int status;
        pid_t childPID = wait(&status);
        printf("status: %x\n", status);
        int randtime = WEXITSTATUS(status);
        printf("Completed Child PID: %d\nSleep Time: %d\n", childPID, randtime);
        printf("Parent Done!\n");
    }
    return 0;
}

int main() {
    set_stack_trace_signal_handler();
    srand((unsigned int) time(NULL));
//    once();
//    once();
    fork_recurse(2);
    return 0;
}
