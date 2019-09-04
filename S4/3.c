#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
void childProccess(char *path, char * arg){
	execl(path, path, arg, 0);
	exit(0);
}
int main(){
	srand(time(NULL));
	while(1){
		char path[100] = {};
		int arg = rand() % 3 + 2;
		printf("%s%d\n", "enter path to wait ", arg);
		scanf("%s", path);
		struct timeval starttime;
		gettimeofday(&starttime, NULL);
		char time[10];
		sprintf(time, "%d", arg);
		pid_t pid = fork();
		if(pid == 0){
			childProccess(path, time);
		}
		waitpid(pid, NULL, WUNTRACED );
		struct timeval endtime;
		gettimeofday(&endtime, NULL);
		printf("time : %ld\n", endtime.tv_sec - starttime.tv_sec);
	}
	return (EXIT_SUCCESS);
}