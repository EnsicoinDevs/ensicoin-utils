#ifndef ENSICOIN_UTILS_AUTOMATA_INV_H
#define ENSICOIN_UTILS_AUTOMATA_INV_H

#include "automata_invvect.h"
#include "automata_varint.h"

struct ensicoin_automata_inv {
	enum ensicoin_automata_inv_state {
		ENSICOIN_AUTOMATA_INV_INVENTORY_COUNT,
		ENSICOIN_AUTOMATA_INV_INVENTORY_COUNT_END,
		ENSICOIN_AUTOMATA_INV_INVVECT,
		ENSICOIN_AUTOMATA_INV_INVVECT_END,
		ENSICOIN_AUTOMATA_INV_END,
		ENSICOIN_AUTOMATA_INV_DISCARDING
	} state;
	uint64_t stateleft;

	union {
		struct ensicoin_automata_varuint inventorycount;
		struct ensicoin_automata_invvect invvect;
	};
};

void
ensicoin_automata_inv_start(struct ensicoin_automata_inv *automata);

enum ensicoin_automata_inv_state
ensicoin_automata_inv_update(struct ensicoin_automata_inv *automata,
	uint8_t byte);

/* ENSICOIN_UTILS_AUTOMATA_INV_H */
#endif
