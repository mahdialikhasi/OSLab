#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#define MAXCHILD 10
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

void childProccess(){
	srand(time(NULL) + getpid());
	int a = (rand() % 5) + 1;
	sleep(a);
	printf("Message from child %d, waited for %d second \n", getpid(), a);
	exit(0);
}
int main(){
	int x = 1;
	time_t timer = time(NULL);
	pid_t pid[MAXCHILD] = {};
	for (int i = 0; i < MAXCHILD; ++i){
		pid[i] = fork();
		if(pid[i] == 0){
			childProccess();
		}		
	}
	while(1){
		sleep(5);
		//if(time(NULL) - timer > 5 * x){
			x++;
			for (int i = 0; i < MAXCHILD; ++i){
				int status;
				waitpid(pid[i], &status, WUNTRACED | WCONTINUED);
				if(status == 0){
					pid[i] = fork();
					if(pid[i] == 0){
						childProccess();
					}
				}				
			}
		//}
	}

	return (EXIT_SUCCESS);
}