//
// Created by kkyse on 11/20/2017.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "stacktrace.h"

#define check(value, func_name) if ((value) == -1) perror(func_name), exit(EXIT_FAILURE)

#define pipe(fds) check(pipe(fds), "pipe")
#define read(fd, buf, size) check(read(fd, buf, size), "read")
#define write(fd, buf, size) check(write(fd, buf, size), "write")
#define close(fd) check(close(fd), "close")

typedef union pipe {
    int fds[2];
    struct {
        int read;
        int write;
    };
} Pipe;

const Pipe open_pipe() {
    Pipe pipe_ = {0};
    pipe(pipe_.fds);
    return pipe_;
}

int main(const int argc, const char *const *const argv) {
    set_stack_trace_signal_handler();
    
    const Pipe pipe1 = open_pipe();
    const Pipe pipe2 = open_pipe();
    
    const pid_t cpid = fork();
    check(cpid, "fork");
    if (cpid == 0) {
        // child
        close(pipe1.write);
        close(pipe2.read);
        
        float x;
        read(pipe1.read, &x, sizeof(x));
        
        printf("[child ] computing x^2 for x = %f\n", x);
        x *= x;
        printf("[child ] sending %f\n", x);
        write(pipe2.write, &x, sizeof(x));
        
        close(pipe1.read);
        close(pipe2.write);
    } else {
        // parent
        close(pipe2.write);
        close(pipe1.read);
        
        srand((unsigned int) time(NULL));
        float x = {rand()};
        printf("[parent] sending %f\n", x);
        write(pipe1.write, &x, sizeof(x));
        
        read(pipe2.read, &x, sizeof(x));
        printf("[parent] received %f\n", x);
        
        close(pipe1.write);
        close(pipe2.read);
    }
}