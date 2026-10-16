#ifndef BOT_PROTOCOL_H
#define BOT_PROTOCOL_H

#define BOT_CLIENT_RECV_TIMEOUT_S 120

typedef enum bot_opcode {
    BOT_OPCODE_HEARTBEAT = 0,
    BOT_OPCODE_SUICIDE = 1,
} bot_opcode;

#endif //BOT_PROTOCOL_H
