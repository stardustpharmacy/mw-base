#ifndef BOT_CLIENT_H
#define BOT_CLIENT_H

#include <stddef.h>
#include <time.h>
#include <bot/networking/protocol.h>

#define BOT_CLIENT_NAME_MAX 32

typedef enum bot_client_state {
    BOT_CLIENT_STATE_PENDING = 0,
    BOT_CLIENT_STATE_KEX = 1,
} bot_client_state;

typedef struct bot_client {
    int fd;
    char name[BOT_CLIENT_NAME_MAX + 1]; /* 32 + null term */
    time_t last_recv_time; /* last msg received (> BOT_RECV_TIMEOUT_S, disconnect) */
    bot_client_state state;
} bot_client;

int bot_client_init(bot_client *client, const char *name);

int bot_client_connect(bot_client *client);

int bot_client_disconnect(bot_client *client);

// TODO: implement a msg pack format
int bot_client_write(bot_client *client, bot_opcode opcode, const void *buf, size_t len);

int bot_client_read(bot_client *client);

#endif //BOT_CLIENT_H
