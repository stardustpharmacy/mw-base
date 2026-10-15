#include <stdlib.h>
#include <string.h>
#include <bot/macros.h>

#include <sys/socket.h>

#include "bot/networking/client.h"

int main(int argc, char *argv[]) {
    BOT_PRINTLN("eee");
    socket(-1, -1, 0);
    BOT_PERROR("socket creation");

    client_t client = {0};
    int ret = bot_client_init(&client, NULL /* TODO: get name from argv[1] */);
    if (ret < 0) {
        BOT_PERROR("Initializing client failed");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
