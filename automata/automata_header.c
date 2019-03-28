#include "automata_header.h"

#include <strings.h>

#define ENSICOIN_HEADER_MAGIC (uint32_t)422021

void
ensicoin_automata_header_start(struct ensicoin_automata_header *automata) {

	automata->state = ENSICOIN_AUTOMATA_HEADER_MAGIC;
	automata->state_left = sizeof(automata->magic);
	automata->magic = 0;
}

enum ensicoin_automata_header_state
ensicoin_automata_header_update(struct ensicoin_automata_header *automata,
	uint8_t byte) {

	switch(automata->state) {
	case ENSICOIN_AUTOMATA_HEADER_MAGIC:
		automata->magic = (automata->magic << 8) | byte;
		if(automata->state_left-- == 0) {
			if(automata->magic == ENSICOIN_HEADER_MAGIC) {
				automata->state = ENSICOIN_AUTOMATA_HEADER_MAGIC_END;
			} else {
				automata->state = ENSICOIN_AUTOMATA_HEADER_DISCARDING;
			}
		}
		break;
	case ENSICOIN_AUTOMATA_HEADER_MAGIC_END:
		automata->state = ENSICOIN_AUTOMATA_HEADER_TYPE;
		automata->state_left = sizeof(automata->type);
		bzero(automata->type, automata->state_left);
		/* fallthrough */
	case ENSICOIN_AUTOMATA_HEADER_TYPE:
		automata->type[sizeof(automata->type) - automata->state_left] = byte;
		if(automata->state_left-- == 0) {
			automata->state = ENSICOIN_AUTOMATA_HEADER_TYPE_END;
		}
		break;
	case ENSICOIN_AUTOMATA_HEADER_TYPE_END:
		automata->state = ENSICOIN_AUTOMATA_HEADER_LENGTH;
		automata->state_left = sizeof(automata->length);
		automata->length = 0;
		/* fallthrough */
	case ENSICOIN_AUTOMATA_HEADER_LENGTH:
		automata->length = (automata->length << 8) | byte;
		if(automata->state_left-- == 0) {
			automata->state = ENSICOIN_AUTOMATA_HEADER_LENGTH_END;
		}
		break;
	case ENSICOIN_AUTOMATA_HEADER_LENGTH_END:
		automata->state = ENSICOIN_AUTOMATA_HEADER_PAYLOAD;
		automata->state_left = automata->length;
		/* fallthrough */
	case ENSICOIN_AUTOMATA_HEADER_PAYLOAD:
		if(automata->state_left-- == 0) {
			automata->state = ENSICOIN_AUTOMATA_HEADER_PAYLOAD_END;
		}
		break;
	case ENSICOIN_AUTOMATA_HEADER_PAYLOAD_END:
		automata->state = ENSICOIN_AUTOMATA_HEADER_DISCARDING;
		/* fallthrough */
	default: /* ENSICOIN_AUTOMATA_HEADER_DISCARDING */
		break;
	}

	return automata->state;
}

