#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
int readNumfromPipe(int pipe){
    int num;
    char buffer[256];
    bzero(buffer,256);
    while( read(pipe,buffer,255)<=0 )
        usleep(500*1000);// 100 ms
    sscanf(buffer, "%d", &num );
    return num;
}
void server(char* path1, char* path2){
	int pipe1;
	char buffer[256];
	bzero(buffer, 256);
	pipe1 = open(path1, O_RDONLY);
	read(pipe1, buffer, 255);
	printf("%s\n", buffer);
	bzero(buffer, 256);
	sleep(100);
	exit(0);
}
int main(){
	int inChild;
	char path1[20];
	char path2[20];
	sprintf(path1, "read.pipe");
	sprintf(path2, "write.pipe");

	mkfifo(path1, 0777);
	mkfifo(path2, 0777);
	pid_t pid = fork();
	if(pid == 0){
		server(path1, path2);
	}
	wait(NULL);
	return (EXIT_SUCCESS);
}