#include "automata_invvect.h"

#define APPEND_BYTE(i, b) ((i) = ((i) << 8) | (b))

void
ensicoin_automata_invvect_start(struct ensicoin_automata_invvect *automata) {

	automata->state = ENSICOIN_AUTOMATA_INVVECT_TYPE_4_LEFT;
	automata->type = 0;
}

enum ensicoin_automata_invvect_state
ensicoin_automata_invvect_update(struct ensicoin_automata_invvect *automata,
	uint8_t byte) {

	switch(automata->state) {
	case ENSICOIN_AUTOMATA_INVVECT_TYPE_1_LEFT:
		APPEND_BYTE(automata->type, byte);
		automata->state = ENSICOIN_AUTOMATA_INVVECT_TYPE_END;
		break;
	case ENSICOIN_AUTOMATA_INVVECT_HASH_1_LEFT:
		automata->hash[0] = byte;
		automata->state = ENSICOIN_AUTOMATA_INVVECT_HASH_END;
		break;
	case ENSICOIN_AUTOMATA_INVVECT_HASH_END:
		automata->state = ENSICOIN_AUTOMATA_INVVECT_HASH_DISCARDING;
		/* fallthrough */
	case ENSICOIN_AUTOMATA_INVVECT_HASH_DISCARDING:
		break;
	case ENSICOIN_AUTOMATA_INVVECT_TYPE_END:
		automata->state = ENSICOIN_AUTOMATA_INVVECT_HASH_32_LEFT;
		bzero(automata->hash, sizeof(automata->hash));
		/* fallthrough */
	default:
		if(automata->state <= ENSICOIN_AUTOMATA_INVVECT_TYPE_4_LEFT) {
			APPEND_BYTE(automata->type, byte);
		} else { /* ENSICOIN_AUTOMATA_INVVECT_HASH_2_LEFT <-> ENSICOIN_AUTOMATA_INVVECT_HASH_32_LEFT */
			automata->hash[sizeof(automata->hash) - (automata->state - (ENSICOIN_AUTOMATA_INVVECT_HASH_1_LEFT - 1))] = byte;
		}
		automata->state--;
		break;
	}

	return automata->state;
}

