#include "automata_address.h"

#include <strings.h>

#define APPEND_BYTE(i, b) ((i) = ((i) << 8) | (b))

void
ensicoin_automata_address_start(struct ensicoin_automata_address *automata) {

	automata->state = ENSICOIN_AUTOMATA_ADDRESS_TIMESTAMP_8_LEFT;
	automata->timestamp = 0;
}

enum ensicoin_automata_address_state
ensicoin_automata_address_update(struct ensicoin_automata_address *automata,
	uint8_t byte) {

	switch(automata->state) {
	case ENSICOIN_AUTOMATA_ADDRESS_TIMESTAMP_1_LEFT:
		APPEND_BYTE(automata->timestamp, byte);
		automata->state = ENSICOIN_AUTOMATA_ADDRESS_TIMESTAMP_END;
		break;
	case ENSICOIN_AUTOMATA_ADDRESS_IP_1_LEFT:
		automata->ip[0] = byte;
		automata->state = ENSICOIN_AUTOMATA_ADDRESS_IP_END;
		break;
	case ENSICOIN_AUTOMATA_ADDRESS_PORT_1_LEFT:
		automata->port |= byte;
		automata->state = ENSICOIN_AUTOMATA_ADDRESS_PORT_END;
		break;
	case ENSICOIN_AUTOMATA_ADDRESS_IP_END:
		automata->state = ENSICOIN_AUTOMATA_ADDRESS_PORT_2_LEFT;
		/* fallthrough */
	case ENSICOIN_AUTOMATA_ADDRESS_PORT_2_LEFT:
		automata->port = byte << 8;
		automata->state = ENSICOIN_AUTOMATA_ADDRESS_PORT_1_LEFT;
		break;
	case ENSICOIN_AUTOMATA_ADDRESS_PORT_END:
		automata->state = ENSICOIN_AUTOMATA_ADDRESS_DISCARDING;
	case ENSICOIN_AUTOMATA_ADDRESS_DISCARDING:
		break;
	case ENSICOIN_AUTOMATA_ADDRESS_TIMESTAMP_END:
		automata->state = ENSICOIN_AUTOMATA_ADDRESS_IP_16_LEFT;
		bzero(automata->ip, sizeof(automata->ip));
		/* fallthrough */
	default:
		if(automata->state <= ENSICOIN_AUTOMATA_ADDRESS_TIMESTAMP_8_LEFT) {
			APPEND_BYTE(automata->timestamp, byte);
		} else { /* ENSICOIN_AUTOMATA_ADDRESS_IP_2_LEFT <-> ENSICOIN_AUTOMATA_ADDRESS_IP_16_LEFT */
			automata->ip[sizeof(automata->ip) - (automata->state - (ENSICOIN_AUTOMATA_ADDRESS_IP_1_LEFT - 1))] = byte;
		}
		automata->state--;
		break;
	}

	return automata->state;
}

