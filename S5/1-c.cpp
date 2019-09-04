#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
using namespace std;
#include <iostream>
int main()
{
	char buffer[256];
	int socket1, portNo;
	struct hostent * server;
	char ipv4[32];
	sprintf(ipv4,"127.0.0.1");
	server = gethostbyname(ipv4);
	struct sockaddr_in server_address;
	portNo = 6000;
	socket1 = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	server_address.sin_family=AF_INET;
	server_address.sin_port = htons(portNo);
	bcopy( (char *)server->h_addr,	(char *)&server_address.sin_addr.s_addr,	server->h_length	);
	connect(socket1,(struct sockaddr *)&server_address,sizeof(server_address));
	//sprintf(buffer,"message from client");
	while(1)
	{
		cout << "enter num 1" << endl;
		cin >> buffer;
		write(socket1,buffer,strlen(buffer));
		cout << "enter num 2" << endl;
		cin >> buffer;
		write(socket1,buffer,strlen(buffer));
		sleep(1);
		bzero(buffer,256);
		read(socket1, buffer, 256);
		cout << buffer << endl;
		bzero(buffer,256);
	}
	return 0;
}