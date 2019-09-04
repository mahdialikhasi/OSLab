#include <iostream>
using namespace std;
#include <algorithm>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string> 
#include <time.h>
#include <signal.h>
using namespace std;
#define MAX_CHILD 3
#define MAX_NUM 200
void child(int fd[2]){
	while(1){
		srand(time(NULL) + getpid());
		int t = rand() % 3 + 1;
		sleep(t);
		int r = rand() % 10;
		//char buffer[255];
		//sprintf(buffer, "%d", r);
		write(fd[1],(void *)&r,sizeof(int));
		cout << "write " << r << endl;
		//cout << r << endl;
	}
	exit(0);
}
int main(){
	srand(time(NULL));
	pid_t pid[MAX_CHILD];
	int x[MAX_CHILD];
	int fd[MAX_CHILD][2];
	int total = 0;
	for (int i = 0; i < MAX_CHILD; ++i)
	{
		x[i] = pipe(fd[i]);
		pid[i] = fork();
		if(pid[i] == 0){
			child(fd[i]);
		}
	}
	cout << "all child created" << endl;
	while(1){
		//sleep(10);
		for (int i = 0; i < MAX_CHILD; ++i)
		{
			int n = 0;
			char buffer[255];
			bzero(buffer, 255);
			read(fd[i][0],(void *)&n,sizeof(int));
			total += n;
			
			cout << "total is : " <<total << endl;
		}
		if(total > MAX_NUM){
			break;
		}
		sleep(1);
	}
	for (int i = 0; i < MAX_CHILD; ++i)
	{
		kill(pid[i], SIGKILL);
	}
	return 0;
}