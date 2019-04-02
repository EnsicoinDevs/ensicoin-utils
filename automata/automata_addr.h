#ifndef ENSICOIN_UTILS_AUTOMATA_ADDR_H
#define ENSICOIN_UTILS_AUTOMATA_ADDR_H

#include "automata_address.h"
#include "automata_varint.h"

struct ensicoin_automata_addr {
	enum ensicoin_automata_addr_state {
		ENSICOIN_AUTOMATA_ADDR_ADDRESSES_COUNT,
		ENSICOIN_AUTOMATA_ADDR_ADDRESSES_COUNT_END,
		ENSICOIN_AUTOMATA_ADDR_ADDRESS,
		ENSICOIN_AUTOMATA_ADDR_ADDRESS_END,
		ENSICOIN_AUTOMATA_ADDR_END,
		ENSICOIN_AUTOMATA_ADDR_DISCARDING
	} state;
	uint64_t stateleft;

	union {
		struct ensicoin_automata_varuint addressescount;
		struct ensicoin_automata_address address;
	};
};

void
ensicoin_automata_addr_start(struct ensicoin_automata_addr *automata);

enum ensicoin_automata_addr_state
ensicoin_automata_addr_update(struct ensicoin_automata_addr *automata,
	uint8_t byte);

/* ENSICOIN_UTILS_AUTOMATA_ADDR_H */
#endif
