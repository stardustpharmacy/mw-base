#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include <bot/networking/client.h>
#include <bot/macros.h>

int bot_client_init(client_t *client, const char *name) {
    if (client == NULL)
        return -1;

    client->fd = -1;

    memset(client->name, 0, sizeof(client->name));
    if (name) strncpy(client->name, name, sizeof(client->name) - 1);

    client->last_recv = 0;

    return 0;
}

int bot_client_connect(client_t *client) {
    if (client == NULL || client->fd >= 0)
        return -1;

    client->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->fd == -1) {
        BOT_PERROR("could not create socket");
        return -1;
    }

    // wtv
    client->last_recv = time(NULL);

    return 0;
}

int bot_client_close(client_t *client) {
    if (client == NULL)
        return -1;

    // duplicated code? yeah kinda rn, do i care? not rly.
    // this will carry other logic l8r on anyway.

    if (client->fd != -1) {
        close(client->fd);
        client->fd = -1;
    }

    client->last_recv = 0;

    return 0;
}
