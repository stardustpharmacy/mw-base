#ifndef BOT_CLIENT_H
#define BOT_CLIENT_H

#include <time.h>
#include <bot/networking/protocol.h>

typedef struct {
    int fd;
    char name[33]; /* 32 + null term */
    time_t last_recv; /* last msg received (> BOT_RECV_TIMEOUT, disconnect) */

    enum {
        BOT_CLIENT_STATE_PENDING = 0,
        BOT_CLIENT_STATE_KEX = 1,
    } state;
} client_t;

int bot_client_init(client_t *client, const char *name);

int bot_client_connect(client_t *client);

int bot_client_close(client_t *client);

// TODO: implement a msg pack format
int bot_client_write(client_t *client, opcode_t opcode, void* buf);

int bot_client_read(client_t *client);

#endif //BOT_CLIENT_H
