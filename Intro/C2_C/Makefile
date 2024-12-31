CC = gcc
CFLAGS = -Wall -Wextra -O2

SERVER_SRC = server/main.c
CLIENT_SRC = client/main.c

SERVER_BIN = server/server
CLIENT_BIN = client/client

all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(SERVER_BIN) $(CLIENT_BIN)

.PHONY: all clean
