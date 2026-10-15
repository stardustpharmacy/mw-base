#ifndef BOT_MACROS_H
#define BOT_MACROS_H

#include <stdbool.h>
#include <stdio.h>

#ifdef BOT_DEBUG
#define BOT_PRINT(fmt, ...) printf("[%s():%d] " fmt, __func__, __LINE__, ##__VA_ARGS__)
#define BOT_PRINTLN(fmt, ...) DEBUG_PRINT(fmt "\n", ##__VA_ARGS__)
#else
#define BOT_PRINT(...) do {} while(0);
#define BOT_PRINTLN(...) do {} while(0);
#endif

#endif //BOT_MACROS_H
