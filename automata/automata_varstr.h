#ifndef ENSICOIN_UTILS_AUTOMATA_VARSTR_H
#define ENSICOIN_UTILS_AUTOMATA_VARSTR_H

#include "automata_varint.h"

struct ensicoin_automata_varstr {
	enum ensicoin_automata_varstr_state {
		ENSICOIN_AUTOMATA_VARSTR_LENGTH,
		ENSICOIN_AUTOMATA_VARSTR_LENGTH_END,
		ENSICOIN_AUTOMATA_VARSTR_STRING,
		ENSICOIN_AUTOMATA_VARSTR_STRING_END,
		ENSICOIN_AUTOMATA_VARSTR_DISCARDING
	} state;
	uint64_t state_left;

	struct ensicoin_automata_varuint length;
};

void
ensicoin_automata_varstr_start(struct ensicoin_automata_varstr *automata);

enum ensicoin_automata_varstr_state
ensicoin_automata_varstr_update(struct ensicoin_automata_varstr *automata,
	uint8_t byte);

/* ENSICOIN_UTILS_AUTOMATA_VARSTR_H */
#endif
