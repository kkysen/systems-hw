//
// Created by kkyse on 11/9/2017.
//

#include <unistd.h>
#include <stdio.h>

int main(const int argc, char **const argv) {
    *argv = "../SignalHandlerExample/sighandler";
    int ret = execvp(*argv, argv);
    perror("execvp");
    return ret;
}