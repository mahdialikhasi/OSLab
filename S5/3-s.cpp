#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
using namespace std;
int readNumfromPipe(int pipe){
    int num;
    char buffer[256];
    bzero(buffer,256);
    while( read(pipe,buffer,255)<=0 )
        usleep(500*1000);// 100 ms
    sscanf(buffer, "%d", &num );
    return num;
}
void writeOnPipe(int num, int pipe)
{
    char buffer[256];
    bzero(buffer,256);
    sprintf(buffer,"%d",num);
    write(pipe,buffer,strlen(buffer));
}
void server(string path1, string path2){
	int pipe1 = open(path1.c_str(), O_RDONLY);
	int pipe2 = open(path2.c_str(), O_WRONLY);
	while(1){
		int a = readNumfromPipe(pipe1);
		int b = readNumfromPipe(pipe1);
		writeOnPipe(a + b, pipe2);
	}
	exit(0);
}
int main(){
	int inChild;
	string path1 = "c2s.pipe";
	string path2 = "s2c.pipe";

	mkfifo(path1.c_str(), 0777);
	mkfifo(path2.c_str(), 0777);
	
		server(path1, path2);
	
	wait(NULL);
	return (EXIT_SUCCESS);
}