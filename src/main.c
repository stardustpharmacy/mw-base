#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include <bot/macros.h>
#include <bot/networking/client.h>

int main(int argc, char *argv[]) {

    bot_client client = {0};
    int ret = bot_client_init(&client, NULL /* TODO: get name from argv[1] */);
    if (ret < 0) {
        BOT_ERROR("Initializing client failed");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
