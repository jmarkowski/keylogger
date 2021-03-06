#ifndef INPUT_ARGS_H
#define INPUT_ARGS_H

#include <stdbool.h>
#include <stdlib.h>     /* for mode_t */

#include "common.h"

typedef struct {
    bool debug;
    char prog_name[MAX_PROG_NAME];
    char keyboard_device[MAX_DEVICE_PATH];

    struct {
        char path[LOG_PATH_LEN];
        char backspace_char;
        mode_t mode;
        int flags;
    } keylog;

    struct {
        uarray_t kill;
        uarray_t pause_resume;
    } seq;
} cmd_args_t;

extern cmd_args_t parse_args(int argc, char *argv[]);
extern mode_t str2mode(const char *mode_str);

#endif
