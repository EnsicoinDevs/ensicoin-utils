#ifndef ENSICOIN_UTILS_AUTOMATA_H
#define ENSICOIN_UTILS_AUTOMATA_H

#include <stdint.h>

struct ensicoin_automata_header {
	enum ensicoin_automata_header_state {
		ENSICOIN_AUTOMATA_HEADER_MAGIC,
		ENSICOIN_AUTOMATA_HEADER_MAGIC_END,
		ENSICOIN_AUTOMATA_HEADER_TYPE,
		ENSICOIN_AUTOMATA_HEADER_TYPE_END,
		ENSICOIN_AUTOMATA_HEADER_LENGTH,
		ENSICOIN_AUTOMATA_HEADER_LENGTH_END,
		ENSICOIN_AUTOMATA_HEADER_PAYLOAD,
		ENSICOIN_AUTOMATA_HEADER_PAYLOAD_END,
		ENSICOIN_AUTOMATA_HEADER_DISCARDING
	} state;
	uint64_t state_left;

	union {
		uint32_t magic;
		char type[12];
		uint64_t length;
	};
};

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
ensicoin_automata_header_start(struct ensicoin_automata_header *automata);

enum ensicoin_automata_header_state
ensicoin_automata_header_update(struct ensicoin_automata_header *automata,
	uint8_t byte);

void
ensicoin_automata_varuint_start(struct ensicoin_automata_varuint *automata);

enum ensicoin_automata_varuint_state
ensicoin_automata_varuint_update(struct ensicoin_automata_varuint *automata,
	uint8_t byte);

/* ENSICOIN_UTILS_AUTOMATA_H */
#endif
