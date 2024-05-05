//Server.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
/*
Define the IP (Internet Protocol) address and port number, that would be used to create a
socket. Here, we are using the localhost address for both the server and the client.
*/
char *ip = "127.0.0.1";
int port = 5566;

//define the variables

int server_sock, client_sock;
struct sockaddr_in server_addr, client_addr;
socklen_t addr_size;
char buffer[1024];
int n;server_sock = socket(AF_INET, SOCK_STREAM, 0);
if (server_sock < 0){
perror("[-]Socket error");
exit(1);
}
printf("[+]TCP server socket created.\n");

/*
Here, we initialize the server address by providing the required
IP and port number. The server keeps all the address information for
both the server and the client in the sockaddr_in struct.
*/

memset(&server_addr, '\0', sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = port;
server_addr.sin_addr.s_addr = inet_addr(ip);

//Binding the socket descriptor with the server address

//information.

n = bind(server_sock, (struct sockaddr*)&server_addr,sizeof(server_addr));
if (n < 0){
perror("[-]Bind error");
exit(1);
}
printf("[+]Bind to the port number: %d\n", port);

//Now, we listen for incoming connections from the clients.

listen(server_sock, 5);
printf("Listening...\n");

/*
the server handles only one client at a time. So, only one client
would communicate and the rest would have to wait for the
communication to get completed.
*/

char c[200];

while(1){
addr_size = sizeof(client_addr);
client_sock = accept(server_sock, (struct sockaddr*)&client_addr,
&addr_size);
printf("[+]Client connected.\n");
while(1){
bzero(buffer, 1024);
recv(client_sock, buffer, sizeof(buffer), 0);
printf("Client: %s\n", buffer);

bzero(buffer, 1024);

printf("Enter the message : ");

fgets(c,200,stdin);

strcpy(buffer, c);
printf("Server: %s\n", buffer);
send(client_sock, buffer, strlen(buffer), 0);

}

close(client_sock);
printf("[+]Client disconnected.\n\n");


}

}
