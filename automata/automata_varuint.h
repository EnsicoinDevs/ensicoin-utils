#ifndef ENSICOIN_UTILS_AUTOMATA_VARUINT_H
#define ENSICOIN_UTILS_AUTOMATA_VARUINT_H

#include <stdint.h>

struct ensicoin_automata_varuint {
	enum ensicoin_automata_varuint_state {
		ENSICOIN_AUTOMATA_VARUINT_START,
		ENSICOIN_AUTOMATA_VARUINT_1_LEFT,
		ENSICOIN_AUTOMATA_VARUINT_2_LEFT,
		ENSICOIN_AUTOMATA_VARUINT_3_LEFT,
		ENSICOIN_AUTOMATA_VARUINT_4_LEFT,
		ENSICOIN_AUTOMATA_VARUINT_5_LEFT,
		ENSICOIN_AUTOMATA_VARUINT_6_LEFT,
		ENSICOIN_AUTOMATA_VARUINT_7_LEFT,
		ENSICOIN_AUTOMATA_VARUINT_8_LEFT,
		ENSICOIN_AUTOMATA_VARUINT_END,
		ENSICOIN_AUTOMATA_VARUINT_DISCARDING
	} state;

	uint64_t value;
};

void
ensicoin_automata_varuint_start(struct ensicoin_automata_varuint *automata);

enum ensicoin_automata_varuint_state
ensicoin_automata_varuint_update(struct ensicoin_automata_varuint *automata,
	uint8_t byte);

/* ENSICOIN_UTILS_AUTOMATA_VARUINT_H */
#endif
