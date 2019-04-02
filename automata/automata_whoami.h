#ifndef ENSICOIN_UTILS_AUTOMATA_WHOAMI_H
#define ENSICOIN_UTILS_AUTOMATA_WHOAMI_H

#include "automata_address.h"
#include "automata_varint.h"

struct ensicoin_automata_whoami {
	enum ensicoin_automata_whoami_state {
		ENSICOIN_AUTOMATA_WHOAMI_VERSION,
		ENSICOIN_AUTOMATA_WHOAMI_VERSION_END,
		ENSICOIN_AUTOMATA_WHOAMI_FROM,
		ENSICOIN_AUTOMATA_WHOAMI_FROM_END,
		ENSICOIN_AUTOMATA_WHOAMI_SERVICES_COUNT,
		ENSICOIN_AUTOMATA_WHOAMI_SERVICES_COUNT_END,
		ENSICOIN_AUTOMATA_WHOAMI_SERVICE,
		ENSICOIN_AUTOMATA_WHOAMI_SERVICE_END,
		ENSICOIN_AUTOMATA_WHOAMI_END,
		ENSICOIN_AUTOMATA_WHOAMI_DISCARDING
	} state;
	uint64_t stateleft;

	union {
		uint32_t version;
		struct ensicoin_automata_address address;
		struct ensicoin_automata_varuint servicescount;
		struct ensicoin_automata_varstr service;
	};
};

void
ensicoin_automata_whoami_start(struct ensicoin_automata_whoami *automata);

enum ensicoin_automata_whoami_state
ensicoin_automata_whoami_update(struct ensicoin_automata_whoami *automata,
	uint8_t byte);

/* ENSICOIN_UTILS_AUTOMATA_WHOAMI_H */
#endif
