#include <stdio.h>
#include <unistd.h>
int main(){
	char path[100], time[10];
	printf("enter path and time of run:"); scanf("%s%s", path, time);
	execl(path, path , time, 0 );
} 