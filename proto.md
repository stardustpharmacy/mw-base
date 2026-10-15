# proto specs

## Conventions

1. all multibyte integers must be encoded in network byte order
2. implementations must validate lengths b4 allocating memory or reading any payloads
3. protocol uses length prefixed blobs for message framing

## Message Framing

the base message format is `[blob_len: u32][blob: bytes]`.<br>
blob_len does not include the 4-byte length prefix

## Key Exchange

before a client is actually considered "connected", clients must exchange keys using the base framing format. the key
exchange uses x25519 to get a shared key. the shared key MUST NOT be used directly as a session key, it should be
derived using a kdf

## Post Key Exchange

after the key exchange, the payload of the base framing uses the following structure:
`[opcode: u8][flags: u8][len: u32][blob: bytes]`. <br>
`len` does not include the header length.

| field  | size   | desc                         |
|--------|--------|------------------------------|
| opcode | 1b     | identifies msg type          |
| flags  | 1b     | message options              |
| len    | 4b     | length of the following blob |
| blob   | `len`b | message specific payload     |

everything after len should be discarded and not counted as part of the blob

### wip lol, its 12 am, im going to sleep gn