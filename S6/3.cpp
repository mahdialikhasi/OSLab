#include <iostream>
using namespace std;
#include <algorithm>
#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXCHILD 5
#define MAXNO 20
int t;
int total = 0;
int pd[2];
void handler(int signo){
	if(signo == SIGUSR2){
		//cout << "response recieved" << endl;
		int x = 0;
		read(pd[0], &x, sizeof(int));
		total += x;
	}else if(signo == SIGUSR1){
		//cout << "signal recieved" << endl;
		t = rand() % 5;
		//cout << t << endl;
		write(pd[1], &t, sizeof(int));
		sleep(1);
		kill(getppid(), SIGUSR2);
	}
}
void child(){
	srand(time(0) + getpid());
	while(1){
		sleep(10);
	}
	exit(0);
}
int main(){
	struct sigaction action;
	action.sa_handler = handler;
	action.sa_mask = (sigset_t){0};
	action.sa_flags = 0;
	sigaction(SIGUSR1, (struct sigaction *) &action, NULL);
	sigaction(SIGUSR2, (struct sigaction *) &action, NULL);
	pipe(pd);
	pid_t pid[MAXCHILD];
	
	for (int i = 0; i < MAXCHILD; ++i)
	{
		pid[i] = fork();
		if(pid[i] == 0){
			child();
		}
	}
	//cout << "children created" << endl;
	sigset_t set1;
	//define signal set named "set1"
	sigemptyset(&set1);
	//making set1 empty
	sigaddset(&set1, SIGUSR2);//adding SIGUSR2 to set1
	while(1){
		for (int i = 0; i < MAXCHILD; ++i){
			kill(pid[i], SIGUSR1);
			cout << "go to pause" << endl;
			cout << "Total :: " << total << endl;
			pause();
			cout << "go out of pause" << endl;
			//sigsuspend(set1);
			if(total > MAXNO)
				break;
		}
		if(total > MAXNO)
			break;
	}
	cout << "total : " << total << endl;
	kill(0, SIGKILL);
	return 0;
}