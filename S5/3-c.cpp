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
int main(){
	string path1 = "c2s.pipe";
	string path2 = "s2c.pipe";
	int a,b;
	int pipe1 = open(path1.c_str(), O_WRONLY);
	int pipe2 = open(path2.c_str(), O_RDONLY);
	printf("num 1: ");
	scanf("%d", &a);
	writeOnPipe(a, pipe1);
	printf("num 2: ");
	scanf("%d", &b);
	writeOnPipe(b, pipe1);
	int c = readNumfromPipe(pipe2);
	cout << "sum is " << c << endl;
	return (EXIT_SUCCESS);
}