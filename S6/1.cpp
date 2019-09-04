#include <iostream>
using namespace std;
#include <algorithm>
#include <stdio.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_TRY 5
int t = 0;
void handler(int signo){
	if(signo == SIGINT){
		if(t == MAX_TRY)
			exit(0);
		cout << endl <<t << " times pressed" << endl;
		t++;
	}
}
int main(){
	struct sigaction action;
	action.sa_handler = handler;
	action.sa_mask = (sigset_t){0};
	action.sa_flags = 0;
	sigaction(SIGINT, (struct sigaction *) &action, NULL);
	while(1){
		cout << "Im running" << endl;
		sleep(5);
	}
	return 0;
}