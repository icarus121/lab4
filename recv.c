#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>
#include <string.h>

int main(int argc , char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char *message, server_reply[2000];

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	else
	{
		printf("Connected successfully.\n");
	}

	server.sin_addr.s_addr = inet_addr("192.168.0.103"); //server ip
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);

	//Connect to remote server
	if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("connect error\n");
		return 1;
	}
	else
	{
		puts("Connected \n");
	}

	//Send some data
	message = "connected between client and server";
	if( send(socket_desc, message, strlen(message), 0) < 0)
	{
		puts("Send failed\n");
		return 1;
	}
	else
	{
		puts("Data Send\n");
		puts(message);
	}

	//Receive a reply from the server
	//receive for sock_stream = recv(sock, &buf, len, flags)

	if(read(socket_desc, server_reply, 2000, 0) < 0)
	{
		puts("recv failed");
	}
	else
	{
		puts("Reply received\n");
		puts(server_reply);
	}
	close(socket_desc);

	return 0;
}
