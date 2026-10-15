#ifndef BOT_MACROS_H
#define BOT_MACROS_H

#include <stdbool.h>
#include <stdio.h>

#ifdef BOT_DEBUG
#define DEBUG_PRINT(fmt, ...) printf("[%s():%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define DEBUG_PRINTLN(fmt, ...) DEBUG_PRINT(fmt "\n", ##__VA_ARGS__)
#else
#define DEBUG_PRINT(...) do {} while(0);
#define DEBUG_PRINTLN(...) do {} while(0);
#endif

#endif //BOT_MACROS_H
