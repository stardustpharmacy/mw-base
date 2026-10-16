#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <bot/macros.h>
#include <bot/networking/client.h>

int bot_client_init(bot_client *client, const char *name) {
    if (client == NULL)
        return -1;

    client->state = BOT_CLIENT_STATE_PENDING;
    client->last_recv_time = 0;
    client->fd = -1;

    memset(client->name, 0, sizeof(client->name));
    if (name) strncpy(client->name, name, sizeof(client->name) - 1);

    return 0;
}

int bot_client_connect(bot_client *client) {
    if (client == NULL || client->fd >= 0)
        return -1;

    // TODO: support IPv6? i hate this shit
    if ((client->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        BOT_ERROR("could not create socket");
        return -1;
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr = inet_addr("127.0.0.1"),
        .sin_port = htons(1337),
    };

    fcntl(client->fd, F_SETFL, O_NONBLOCK | fcntl(client->fd, F_GETFL, 0));

    const int ret = connect(client->fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
    if (ret == -1 && errno != EINPROGRESS) {
        BOT_ERROR("initializing connection failed");
        bot_client_disconnect(client);
        return -1;
    }

    // wtv
    client->last_recv_time = time(NULL);

    return 0;
}

int bot_client_disconnect(bot_client *client) {
    if (client == NULL)
        return -1;

    // duplicated code? yeah kinda rn, do i care? not rly.
    // this will carry other logic l8r on anyway.

    if (client->fd != -1) {
        close(client->fd);
        client->fd = -1;
    }

    client->last_recv_time = 0;
    client->state = BOT_CLIENT_STATE_PENDING;

    return 0;
}
