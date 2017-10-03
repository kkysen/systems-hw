//
// Created by kkyse on 9/24/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

#define SHELL "shell"

void init_shell() {

}

void free_shell() {

}

char *read_line() {
    char *line = NULL;
    size_t buf_size = 0;
    getline(&line, &buf_size, stdin);
    return line;
}

const char *const *const parse_line(const char *const line) {
    return NULL; // TODO
}

static inline void shell_error() {
    perror(SHELL);
}

int launch(const char *const *const args) {
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(args[0], (char *const *const) args) == -1) {
            shell_error();
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        shell_error();
    } else {
        int status;
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

typedef struct Builtin {
    const char *const name;
    int (*const call)(const char *const *const);
} Builtin;

int cd_shell(const char *const *const args) {
    const char *const arg = args[1];
    if (arg == NULL) {
        fprintf(stderr, "shell: expected argument to \"cd\"");
    } else {
        if (chdir(arg) != 0) {
            shell_error();
        }
    }
    return 1;
}

int exit_shell(const char *const *const args) {
    return 0; // terminate while(status) loop
}

const Builtin builtins[] = {
    {"cd", &cd_shell},
    {"exit", &exit_shell},
};

#define array_size(array) (sizeof((array)) / sizeof(*(array)))

int execute(const char *const *const args) {
    if (args[0] == NULL) {
        return 1;
    }
    const char *const name = args[0];
    #pragma unroll array_size(builtins)
    for (uint i = 0; i < array_size(builtins); ++i) {
        Builtin builtin = builtins[i];
        if (strcmp(name, builtin.name) == 0) {
            return builtin.call(args);
        }
    }
    // TODO builtins
    launch(args);
}

void loop() {
    int status;
    do {
        printf(">");
        char *const line = read_line();
        const char *const *const args = parse_line(line);
        status = execute(args);
        free(line);
        free((const char **) args);
    } while (status);
}

int main(const int argc, const char *const *const argv) {
    init_shell();
    loop();
    free_shell();
}