#include "automata_varstr.h"

void
ensicoin_automata_varstr_start(struct ensicoin_automata_varstr *automata) {

	automata->state = ENSICOIN_AUTOMATA_VARSTR_LENGTH;
	ensicoin_automata_varuint_start(&automata->length);
}

enum ensicoin_automata_varstr_state
ensicoin_automata_varstr_update(struct ensicoin_automata_varstr *automata,
	uint8_t byte) {

	switch(automata->state) {
	case ENSICOIN_AUTOMATA_VARSTR_LENGTH:
		switch(ensicoin_automata_varuint_update(&automata->length, byte)) {
		case ENSICOIN_AUTOMATA_VARUINT_END:
			automata->state = ENSICOIN_AUTOMATA_VARSTR_LENGTH_END;
			break;
		case ENSICOIN_AUTOMATA_VARUINT_DISCARDING:
			automata->state = ENSICOIN_AUTOMATA_VARSTR_DISCARDING;
			break;
		default:
			break;
		}
		break;
	case ENSICOIN_AUTOMATA_VARSTR_LENGTH_END:
		automata->state = ENSICOIN_AUTOMATA_VARSTR_STRING;
		automata->state_left = automata->length.value;
	case ENSICOIN_AUTOMATA_VARSTR_STRING:
		if(automata->state_left-- == 0) {
			automata->state = ENSICOIN_AUTOMATA_VARSTR_STRING_END;
		}
		break;
	case ENSICOIN_AUTOMATA_VARSTR_STRING_END:
		automata->state = ENSICOIN_AUTOMATA_VARSTR_DISCARDING;
		/* fallthrough */
	default: /* ENSICOIN_AUTOMATA_VARSTR_DISCARDING */
		break;
	}

	return automata->state;
}

