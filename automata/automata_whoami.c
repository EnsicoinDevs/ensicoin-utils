#include "automata_whoami.h"

#define APPEND_BYTE(i, b) ((i) = ((i) << 8) | (b))

void
ensicoin_automata_whoami_start(struct ensicoin_automata_whoami *automata) {

	automata->state = ENSICOIN_AUTOMATA_WHOAMI_VERSION;
	automata->stateleft = sizeof(automata->version);
}

enum ensicoin_automata_whoami_state
ensicoin_automata_whoami_update(struct ensicoin_automata_whoami *automata,
	uint8_t byte) {

	switch(automata->state) {
	case ENSICOIN_AUTOMATA_WHOAMI_VERSION:
		APPEND_BYTE(automata->version, byte);
		if(automata->stateleft-- == 0) {
			automata->state = ENSICOIN_AUTOMATA_WHOAMI_VERSION_END;
		}
		break;
	case ENSICOIN_AUTOMATA_WHOAMI_VERSION_END:
		automata->state = ENSICOIN_AUTOMATA_WHOAMI_FROM;
		ensicoin_automata_address_start(&automata->address);
		/* fallthrough */
	case ENSICOIN_AUTOMATA_WHOAMI_FROM:
		switch(ensicoin_automata_address_update(&automata->address, byte)) {
		case ENSICOIN_AUTOMATA_ADDRESS_PORT_END:
			automata->state = ENSICOIN_AUTOMATA_WHOAMI_FROM_END;
			break;
		case ENSICOIN_AUTOMATA_ADDRESS_DISCARDING:
			automata->state = ENSICOIN_AUTOMATA_WHOAMI_DISCARDING;
			break;
		default:
			break;
		}
		break;
	case ENSICOIN_AUTOMATA_WHOAMI_FROM_END:
		automata->state = ENSICOIN_AUTOMATA_WHOAMI_SERVICES_COUNT;
		ensicoin_automata_varuint_start(&automata->servicescount);
		/* fallthrough */
	case ENSICOIN_AUTOMATA_WHOAMI_SERVICES_COUNT:
		switch(ensicoin_automata_varuint_update(&automata->servicescount, byte)) {
		case ENSICOIN_AUTOMATA_VARUINT_END:
			automata->state = ENSICOIN_AUTOMATA_WHOAMI_SERVICES_COUNT_END;
			break;
		case ENSICOIN_AUTOMATA_VARUINT_DISCARDING:
			automata->state = ENSICOIN_AUTOMATA_WHOAMI_DISCARDING;
			break;
		default:
			break;
		}
		break;
	case ENSICOIN_AUTOMATA_WHOAMI_SERVICES_COUNT_END:
		automata->stateleft = automata->servicescount.value;
		ensicoin_automata_varstr_start(&automata->service);
		/* fallthrough */
	case ENSICOIN_AUTOMATA_WHOAMI_SERVICE_END:
		automata->state = ENSICOIN_AUTOMATA_WHOAMI_SERVICE;
		/* fallthrough */
	case ENSICOIN_AUTOMATA_WHOAMI_SERVICE:
		switch(ensicoin_automata_varstr_update(&automata->service, byte)) {
		case ENSICOIN_AUTOMATA_VARSTR_END:
			if(automata->stateleft-- == 0) {
				automata->state = ENSICOIN_AUTOMATA_WHOAMI_END;
			} else {
				automata->state = ENSICOIN_AUTOMATA_WHOAMI_SERVICE_END;
			}
			break;
		case ENSICOIN_AUTOMATA_VARSTR_DISCARDING:
			automata->state = ENSICOIN_AUTOMATA_WHOAMI_DISCARDING;
			break;
		default:
			break;
		}
		break;
	case ENSICOIN_AUTOMATA_WHOAMI_END:
		automata->state = ENSICOIN_AUTOMATA_WHOAMI_DISCARDING;
		/* fallthrough */
	default: /* ENSICOIN_AUTOMATA_WHOAMI_DISCARDING */
		break;
	}

	return automata->state;
}

