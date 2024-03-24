//Client.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
/*
NOTE: Make sure that the IP address and the port number for the client are the same as
the server.
*/
char *ip = "127.0.0.1";
int port = 5566;
int sock;
struct sockaddr_in addr;
socklen_t addr_size;
char buffer[1024];
int n;

/*
We start by creating a TCP (Transmission Control Protocol) socket. The socket would be
used to connect to the server and start communication.
*/

sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock < 0){
perror("[-]Socket error");
exit(1);
}
printf("[+]TCP server socket created.\n");

//provide the required IP address and the port number to the required data structures.
memset(&addr, '\0', sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_port = port;
addr.sin_addr.s_addr = inet_addr(ip);

//We send a connection request to the server and wait for the server to accept the request.

connect(sock, (struct sockaddr*)&addr, sizeof(addr));
printf("Connected to the server.\n");

//We send a message to the server and wait for the reply.
bzero(buffer, 1024);

char k[200];
while(1){

printf("Enter the message : ");

fgets(k,200,stdin);
strcpy(buffer, k);

printf("Client: %s\n", buffer);
send(sock, buffer, strlen(buffer), 0);

/* We receive the reply from the server and print it on the console.*/

bzero(buffer, 1024);
recv(sock, buffer, sizeof(buffer), 0);
printf("Server: %s\n", buffer);

}

//At last, we close the connection from the server.
close(sock);
printf("Disconnected from the server.\n");
return 0;
}
