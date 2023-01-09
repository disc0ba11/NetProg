.PHONY: all debug release client server clean

RELEASE_FLAGS = -O2 -Wall -DNDEBUG
DEBUG_FLAGS = -g -O0 -Wall
CLIENT_RELEASE_EXEC = daytime_client
SERVER_RELEASE_EXEC = daytime_server
CLIENT_DEBUG_EXEC = daytime_client-dbg
SERVER_DEBUG_EXEC = daytime_server-dbg
CLIENT_SRC = daytime_client.cpp
SERVER_SRC = daytime_server.cpp

all: debug release

debug: $(CLIENT_DEBUG_EXEC) $(SERVER_DEBUG_EXEC)
$(CLIENT_DEBUG_EXEC): $(CLIENT_SRC)
	g++ $(DEBUG_FLAGS) $(CLIENT_SRC) -o $(CLIENT_DEBUG_EXEC)
$(SERVER_DEBUG_EXEC): $(SERVER_SRC)
	g++ $(DEBUG_FLAGS) $(SERVER_SRC) -o $(SERVER_DEBUG_EXEC)

release: client server

client:
	g++ $(RELEASE_FLAGS) $(CLIENT_SRC) -o $(CLIENT_RELEASE_EXEC)

server:
	g++ $(RELEASE_FLAGS) $(SERVER_SRC) -o $(SERVER_RELEASE_EXEC)

clean:
	rm -f $(CLIENT_RELEASE_EXEC) $(SERVER_RELEASE_EXEC) $(CLIENT_DEBUG_EXEC) $(SERVER_DEBUG_EXEC)
