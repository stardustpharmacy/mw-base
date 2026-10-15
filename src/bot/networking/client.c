#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <bot/networking/client.h>
#include <bot/macros.h>

int bot_client_init(client_t *client, const char *name) {
    if (client == NULL)
        return -1;

    client->state = BOT_CLIENT_STATE_PENDING;
    client->last_recv = 0;
    client->fd = -1;

    memset(client->name, 0, sizeof(client->name));
    if (name) strncpy(client->name, name, sizeof(client->name) - 1);

    return 0;
}

int bot_client_connect(client_t *client) {
    if (client == NULL || client->fd >= 0)
        return -1;

    // TODO: support IPv6? i hate this shit
    if ((client->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        BOT_PERROR("could not create socket");
        return -1;
    }

    struct sockaddr_in tmp = {
        .sin_family = AF_INET,
        .sin_addr = inet_addr("127.0.0.1"),
        .sin_port = htons(1337),
    };

    fcntl(client->fd, F_SETFL, O_NONBLOCK | fcntl(client->fd, F_GETFL, 0));

    const int ret = connect(client->fd, (struct sockaddr *) &tmp, sizeof(struct sockaddr_in));
    if (ret == -1 && errno != EINPROGRESS) {
        BOT_PERROR("initializing connection failed");
        bot_client_close(client);
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
    client->state = BOT_CLIENT_STATE_PENDING;

    return 0;
}
