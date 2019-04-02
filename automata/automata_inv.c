#include "automata_inv.h"

#define APPEND_BYTE(i, b) ((i) = ((i) << 8) | (b))

void
ensicoin_automata_inv_start(struct ensicoin_automata_inv *automata) {

	automata->state = ENSICOIN_AUTOMATA_INV_INVENTORY_COUNT;
	ensicoin_automata_varuint_start(&automata->inventorycount);
}

enum ensicoin_automata_inv_state
ensicoin_automata_inv_update(struct ensicoin_automata_inv *automata,
	uint8_t byte) {

	switch(automata->state) {
	case ENSICOIN_AUTOMATA_INV_INVENTORY_COUNT:
		switch(ensicoin_automata_varuint_update(&automata->inventorycount, byte)) {
		case ENSICOIN_AUTOMATA_VARUINT_END:
			automata->state = ENSICOIN_AUTOMATA_INV_INVENTORY_COUNT_END;
			break;
		case ENSICOIN_AUTOMATA_VARUINT_DISCARDING:
			automata->state = ENSICOIN_AUTOMATA_INV_DISCARDING;
			break;
		default:
			break;
		}
		break;
	case ENSICOIN_AUTOMATA_INV_INVENTORY_COUNT_END:
		automata->stateleft = automata->inventorycount.value;
		ensicoin_automata_invvect_start(&automata->invvect);
		/* fallthrough */
	case ENSICOIN_AUTOMATA_INV_INVVECT_END:
		automata->state = ENSICOIN_AUTOMATA_INV_INVVECT;
		/* fallthrough */
	case ENSICOIN_AUTOMATA_INV_INVVECT:
		switch(ensicoin_automata_invvect_update(&automata->invvect, byte)) {
		case ENSICOIN_AUTOMATA_INVVECT_END:
			if(automata->stateleft-- == 0) {
				automata->state = ENSICOIN_AUTOMATA_INV_END;
			} else {
				automata->state = ENSICOIN_AUTOMATA_INV_INVVECT_END;
			}
			break;
		case ENSICOIN_AUTOMATA_INVVECT_DISCARDING:
			automata->state = ENSICOIN_AUTOMATA_INV_DISCARDING;
			break;
		default:
			break;
		}
		break;
	case ENSICOIN_AUTOMATA_INV_END:
		automata->state = ENSICOIN_AUTOMATA_INV_DISCARDING;
		/* fallthrough */
	default: /* ENSICOIN_AUTOMATA_INV_DISCARDING */
		break;
	}

	return automata->state;
}

