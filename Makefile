CC=clang
CFLAGS=-Wall
ENSICOIN_ENFORCER_SRC=src/enforcer.c
ENSICOIN_ENFORCER=build/bin/ensicoin-enforcer
BUILDDIRS=build/bin/

all: $(BUILDDIRS) $(ENSICOIN_ENFORCER)

$(BUILDDIRS):
	mkdir -p $@

$(ENSICOIN_ENFORCER): $(ENSICOIN_ENFORCER_SRC)
	$(CC) $(CFLAGS) -o $@ $^

