#ifndef ENSICOIN_UTILS
#define ENSICOIN_UTILS

#include <stdint.h>
#include <stdbool.h>

struct ensicoin_signature;
struct ensicoin_public_key;
struct ensicoin_private_key;

bool
ensicoin_verify(const struct ensicoin_public_key *pubkey,
	const struct ensicoin_signature *sig,
	const uint8_t *data, size_t datalen);

void
ensicoin_verify(const struct ensicoin_public_key *pubkey,
	const uint8_t *data, size_t datalen);

/* ENSICOIN_UTILS */
#endif
