#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <poll.h>
#include <stdlib.h>
#include <unistd.h>

#include <bot/macros.h>
#include <bot/networking/client.h>

int main(int argc, char *argv[]) {
    bot_client client = {0};

    int ret = bot_client_init(&client, NULL /* TODO: get name from argv[1] */);
    if (ret < 0) {
        BOT_ERROR("initializing client failed");
        return EXIT_FAILURE;
    }

    // shit code industry
    while (true) {
        if (client.fd < 0) {
            ret = bot_client_connect(&client);

            if (ret < 0) {
                bot_client_disconnect(&client, true);
                BOT_ERROR("failed to connect to the server");
                continue;
            }
        }

        // we will need to poll more stuff eventually
        // so just alr make it an array ig
        struct pollfd pfds[1] = {0};
        pfds[0] = (struct pollfd){
            .fd = client.fd,
            .events = client.poll_events,
        };

        const int nfds = poll(pfds, 1, 50);
        if (nfds < 0) {
            if (errno == EINTR)
                continue;

            break;
        }

        // tick da boat
        if (nfds == 0) {
            ret = bot_client_tick(&client);
            if (ret < 0) {
                BOT_PRINTLN("handling client tick errored, disconnecting");
                bot_client_disconnect(&client, true);
            }
            continue;
        }

        for (int i = 0; i < nfds; ++i) {
            if (pfds[i].revents == 0)
                continue;

            if (pfds[i].fd == client.fd) {
                ret = bot_client_events(&client, pfds[i].revents);
                if (ret < 0) {
                    BOT_PRINTLN("handling client events errored, disconnecting");
                    bot_client_disconnect(&client, true);
                }
            }
        }
    }

    bot_client_disconnect(&client, false);
    return EXIT_SUCCESS;
}
