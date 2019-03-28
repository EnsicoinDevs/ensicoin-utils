#ifndef ENSICOIN_UTILS_AUTOMATA_INVVECT_H
#define ENSICOIN_UTILS_AUTOMATA_INVVECT_H

#include <stdint.h>

struct ensicoin_automata_invvect {
	enum ensicoin_automata_invvect_state {
		ENSICOIN_AUTOMATA_INVVECT_TYPE_1_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_TYPE_2_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_TYPE_3_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_TYPE_4_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_TYPE_END,
		ENSICOIN_AUTOMATA_INVVECT_HASH_1_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_2_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_3_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_4_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_5_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_6_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_7_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_8_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_9_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_10_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_11_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_12_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_13_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_14_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_15_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_16_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_17_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_18_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_19_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_20_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_21_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_22_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_23_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_24_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_25_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_26_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_27_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_28_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_29_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_30_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_31_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_32_LEFT,
		ENSICOIN_AUTOMATA_INVVECT_HASH_END,
		ENSICOIN_AUTOMATA_INVVECT_DISCARDING
	} state;

	union {
		uint32_t type;
		uint8_t hash[32];
	};
};

void
ensicoin_automata_invvect_start(struct ensicoin_automata_invvect *automata);

enum ensicoin_automata_invvect_state
ensicoin_automata_invvect_update(struct ensicoin_automata_invvect *automata,
	uint8_t byte);

/* ENSICOIN_UTILS_AUTOMATA_INVVECT_H */
#endif
