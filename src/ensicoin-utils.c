#include "ensicoin-utils.h"

bool
ensicoin_verify(const struct ensicoin_public_key *pubkey,
	const struct ensicoin_signature *sig,
	const uint8_t *data, size_t datalen) {

	return false;
}

void
ensicoin_verify(const struct ensicoin_public_key *pubkey,
	const uint8_t *data, size_t datalen) {
}

