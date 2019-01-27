CC=clang
CFLAGS=-Wall
SRC=$(wildcard src/*.c)
LIB=ensicoin-utils.so

all: $(LIB)

$(LIB): $(SRC)
	$(CC) $(CFLAGS) -shared -fPIC -o $@ $^
