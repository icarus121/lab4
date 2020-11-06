#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>  //inet_addr
#include <unistd.h>
#include <string.h>

int main(int argc , char *argv[])
{
        int socket_desc, new_socket, c;
        struct sockaddr_in server, client;
        char *message, server_reply[2000], msg[2000];

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

	c = sizeof(struct sockaddr_in);
	//new_socket = connect(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);

	if (new_socket<0)
        {
                perror("accept failed.\n");
               	return 1;
        }

	 int s = send(socket_desc, msg, strlen(msg), 0);
         if( s < 0)
        {
                puts("Send failed\n");
                return 1;
        }
        else
        {
                printf("Enter data:");
                scanf("%2000s \n", msg);
                puts("Data Send \n");
                //puts(message);
        }

        //Receive a reply from the server
        //receive for sock_stream = recv(sock, &buf, len, flags)
	while(1){
	//int n;
	int n = recv(socket_desc, server_reply, 2000, 0);
	read(socket_desc, server_reply, n);
       	puts("Received success\n");
	puts(server_reply);

	int s = send(socket_desc, msg, strlen(msg), 0);
	 if( s < 0)
        {
                puts("Send failed\n");
                return 1;
        }
        else
        {
                printf("Enter data:");
                scanf("%2000s \n", msg);
                puts("Data Send \n");
                //puts(message);
        }
	}

	//while(1){
	/*int n = recv(socket_desc, server_reply, 2000, 0);
        read(socket_desc, server_reply, n);
        puts("Received success\n");
	puts(server_reply);*/
	//}


	//send(new_socket, msg, 2000, 0);
	//puts(msg);
	//close(new_socket);
       	close(socket_desc);

        return 0;
}

