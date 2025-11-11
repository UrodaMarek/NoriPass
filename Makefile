CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
OBJ = src/main.o src/ui.o src/storage.o src/crypto.o
LIBS = -lncurses

all: noripass

noripass: $(OBJ)
	$(CC) $(OBJ) -o noripass $(LIBS)

clean:
	rm -f $(OBJ) noripass