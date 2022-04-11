## TCP/IP

Two simple programms. Server accept new conection in main procces and after that read string and write to socket. Client connect to server and send input line from standart input, and received it from server.

Compile:

    make all
    or
    gcc Server.c -o bin/Server -pthread
	gcc Client.c -o bin/Client -pthread

Launch: 

    bin/Server
    bin/Client <ip addres of server>


