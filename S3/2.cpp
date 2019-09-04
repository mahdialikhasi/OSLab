#include <iostream>
using namespace std;
#include <algorithm>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char ** argv){
	
	for (int i = strtol(argv[4], NULL , 10); i < strtol(argv[5], NULL, 10) + 1; ++i)
	{
		char buff[1] = {};
		char name[strlen(argv[1]) + strlen(argv[2]) + 5 + strlen(argv[3])];
		sprintf(name, "%s%s%d%s\0", argv[1], argv[2], i, argv[3]);
		int fd = open(name, O_CREAT | O_RDWR, 0755);
		write(fd, (void *)buff, 10);
	}

	
	return 0;
}