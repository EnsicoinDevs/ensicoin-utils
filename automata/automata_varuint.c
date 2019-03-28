#include "automata.h"

void
ensicoin_automata_varuint_start(struct ensicoin_automata_varuint *automata) {

	automata->state = ENSICOIN_AUTOMATA_VARUINT_START;
	automata->value = 0;
}

enum ensicoin_automata_varuint_state
ensicoin_automata_varuint_update(struct ensicoin_automata_varuint *automata,
	uint8_t byte) {

	switch(automata->state) {
	case ENSICOIN_AUTOMATA_VARUINT_START:
		if(byte < 0xFD) {
			automata->value = byte;
			automata->state = ENSICOIN_AUTOMATA_VARUINT_END;
		} else {
			automata->state = 1 << (byte & 0x03)
				+ (ENSICOIN_AUTOMATA_VARUINT_1_LEFT - 1);
		}
		break;
	case ENSICOIN_AUTOMATA_VARUINT_END:
		automata->state = ENSICOIN_AUTOMATA_VARUINT_DISCARDING;
		/* fallthrough */
	case ENSICOIN_AUTOMATA_VARUINT_DISCARDING:
		break;
	case ENSICOIN_AUTOMATA_VARUINT_1_LEFT:
		automata->value = (automata->value << 8) | byte;
		automata->state = ENSICOIN_AUTOMATA_VARUINT_END;
		break;
	default: /* ENSICOIN_AUTOMATA_VARUINT_2_LEFT <-> ENSICOIN_AUTOMATA_VARUINT_8_LEFT */
		automata->value = (automata->value << 8) | byte;
		automata->state--;
		break;
	}
}

