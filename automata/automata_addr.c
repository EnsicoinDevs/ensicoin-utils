#include "automata_addr.h"

#define APPEND_BYTE(i, b) ((i) = ((i) << 8) | (b))

void
ensicoin_automata_addr_start(struct ensicoin_automata_addr *automata) {

	automata->state = ENSICOIN_AUTOMATA_ADDR_ADDRESSES_COUNT;
	ensicoin_automata_varuint_start(&automata->servicescount);
}

enum ensicoin_automata_addr_state
ensicoin_automata_addr_update(struct ensicoin_automata_addr *automata,
	uint8_t byte) {

	switch(automata->state) {
	case ENSICOIN_AUTOMATA_ADDR_ADDRESSES_COUNT:
		switch(ensicoin_automata_varuint_update(&automata->addressescount, byte)) {
		case ENSICOIN_AUTOMATA_VARUINT_END:
			automata->state = ENSICOIN_AUTOMATA_ADDR_ADDRESSES_COUNT_END;
			break;
		case ENSICOIN_AUTOMATA_VARUINT_DISCARDING:
			automata->state = ENSICOIN_AUTOMATA_ADDR_DISCARDING;
			break;
		default:
			break;
		}
		break;
	case ENSICOIN_AUTOMATA_ADDR_ADDRESSES_COUNT_END:
		automata->stateleft = automata->addressescount.value;
		ensicoin_automata_address_start(&automata->address);
		/* fallthrough */
	case ENSICOIN_AUTOMATA_ADDR_ADDRESS_END:
		automata->state = ENSICOIN_AUTOMATA_ADDR_ADDRESS;
		/* fallthrough */
	case ENSICOIN_AUTOMATA_ADDR_ADDRESS:
		switch(ensicoin_automata_address_update(&automata->address, byte)) {
		case ENSICOIN_AUTOMATA_ADDRESS_END:
			if(automata->stateleft-- == 0) {
				automata->state = ENSICOIN_AUTOMATA_ADDR_END;
			} else {
				automata->state = ENSICOIN_AUTOMATA_ADDR_ADDRESS_END;
			}
			break;
		case ENSICOIN_AUTOMATA_ADDRESS_DISCARDING:
			automata->state = ENSICOIN_AUTOMATA_ADDR_DISCARDING;
			break;
		default:
			break;
		}
		break;
	case ENSICOIN_AUTOMATA_ADDR_END:
		automata->state = ENSICOIN_AUTOMATA_ADDR_DISCARDING;
		/* fallthrough */
	default: /* ENSICOIN_AUTOMATA_ADDR_DISCARDING */
		break;
	}

	return automata->state;
}

