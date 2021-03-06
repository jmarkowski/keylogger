#ifndef COMMON_H
#define COMMON_H

/* Utility defines */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define BIT(shift) (1 << (shift))

#define OK 0
#define ERROR -1

/* Shared defines */
#define LOG_PATH_LEN 128
#define MAX_PROG_NAME 12
#define MAX_DEVICE_PATH 100

typedef struct uarray {
    unsigned *el;
    unsigned size;
} uarray_t;

#endif
