#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string> 
using namespace std;
#define MAX_CHILD 20
int main(){
	char buffer[256];
	int socket1, portNo, clientLength;
	int acceptedSocket;
	struct hostent * server;
	char ipv4[32];
	sprintf(ipv4,"127.0.0.1");
	server = gethostbyname(ipv4);
	struct sockaddr_in server_address, client_address;
	clientLength = sizeof(client_address);
	portNo = 6000;
	
	// making socket family = AF_INET, type = SOCK_STREAM , protocol = TCP
	socket1 = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	//initializing server addres
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(portNo);
	server_address.sin_addr.s_addr = INADDR_ANY;
	//binding socket to server address
	bind ( socket1, (struct sockaddr*) &server_address,sizeof(server_address));
	//listening to incoming requests from clients
	listen(socket1,MAX_CHILD);
	acceptedSocket = accept( socket1, (struct sockaddr * )&client_address,(socklen_t *)&clientLength);
	bzero(buffer,256);
	int n;
	while(1)
	{
		
		bzero(buffer,256);
		read(acceptedSocket, buffer, 256);
		printf("[%s@%d]# %s\n", ipv4, portNo, buffer);
		sleep(1);
		int a = strtol(buffer, NULL, 10);
		bzero(buffer,256);
		read(acceptedSocket, buffer, 256);
		int b = strtol(buffer, NULL, 10);
		printf("[%s@%d]# %s\n", ipv4, portNo, buffer);
		sleep(1);
		bzero(buffer,256);
		//sprintf(buffer, "%d + %d", a, b);
		int c = a + b;
		strcpy(buffer, to_string(c).c_str());
		write(acceptedSocket,buffer,strlen(buffer));
		//bzero(buffer,256);
		sleep(1);
	}
	return 0;
}