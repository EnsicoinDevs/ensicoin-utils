#ifndef ENSICOIN_UTILS_AUTOMATA_HEADER_H
#define ENSICOIN_UTILS_AUTOMATA_HEADER_H

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

void
ensicoin_automata_header_start(struct ensicoin_automata_header *automata);

enum ensicoin_automata_header_state
ensicoin_automata_header_update(struct ensicoin_automata_header *automata,
	uint8_t byte);

/* ENSICOIN_UTILS_AUTOMATA_HEADER_H */
#endif
