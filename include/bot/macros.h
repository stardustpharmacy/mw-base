#ifndef BOT_MACROS_H
#define BOT_MACROS_H

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef BOT_DEBUG

#define BOT_PRINT(fmt, ...) printf("[%s():%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define BOT_PRINTLN(fmt, ...) BOT_PRINT(fmt "\n", ##__VA_ARGS__)

#define BOT_ERROR(...) do { \
    int err_ = errno; \
    BOT_PRINT(__VA_ARGS__); \
    printf(": %s\n", strerror(err_)); \
} while(0);

#else
#define BOT_PRINT(...) do {} while(0);
#define BOT_PRINTLN(...) do {} while(0);
#define BOT_ERROR(...) do {} while(0);
#endif

#endif //BOT_MACROS_H
