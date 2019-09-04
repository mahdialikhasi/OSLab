#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void childProccess(){
	printf("%d\n", getpid());
	exit(0);
}
int main(){
	while(true){
		pid_t pid = fork();
		if(pid == 0){
			childProccess();
		}
		sleep(2);
	}
	return (EXIT_SUCCESS);
}