#include <algorithm>
#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAXIMUM 20
#define MAX_CHILD 5
int total = 0;
pid_t pid[MAX_CHILD];
void handler(int signo){
	if(signo == SIGUSR1){
		total++;
		printf("%s %d\n","total is ", total);
		if(total >= MAXIMUM){
			for (int i = 0; i < MAX_CHILD; ++i)
			{
				kill(pid[i], SIGKILL);
			}
			kill(getpid(), SIGKILL);
		} 
	}
}
void childprocess(int parentid){
	srand(time(NULL) + getpid());
	int s = rand() % 5 + 2;
	while(1){
		sleep(s);
		kill(parentid, SIGUSR1);
	}
}
int main(){
	int x = getpid();
	for (int i = 0; i < MAX_CHILD; ++i)
	{
		pid[i] = fork();
		if(pid[i] == 0){
			childprocess(x);
			exit(0);
		}
	}
	struct sigaction action;
	action.sa_handler = handler;
	action.sa_mask = (sigset_t){0};
	action.sa_flags = 0;
	sigaction(SIGUSR1, (struct sigaction *) &action, NULL);
	while(1){
		sleep(5);
	}
	return 0;
}