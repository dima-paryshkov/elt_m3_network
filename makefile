Server: Server.c
	gcc Server.c -o bin/Server -pthread

Client: Client.c
	gcc Client.c -o bin/Client -pthread

all: Server.c Client.c
	gcc Server.c -o bin/Server -pthread
	gcc Client.c -o bin/Client -pthread

