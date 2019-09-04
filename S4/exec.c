#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	if(argc != 2){

		printf("%s %d\n", "argument failed\n", argc);
		exit(EXIT_FAILURE);
	}
	printf("%s%s%s\n", "i'm going to sleep ", argv[1], " sec");
	sleep(atoi(argv[1]));
	return 0;
}