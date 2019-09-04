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
	
	if(!strcmp(argv[1], "-vector")){
		int a = strtol(argv[2], NULL, 10);
		int fd = open(argv[3], O_RDWR | O_CREAT, 00755);
		int tmp[a];
		for (int i = 0; i < a; ++i)
		{
			cin >> tmp[i];
		}
		write(fd, (void *)tmp, a * sizeof(int));
		close(fd);
	}else if(!strcmp(argv[1], "-readVec")){
		if(argc == 3){
			int t;
			int fd = open(argv[2], O_RDWR);
			cout << "{ ";
			while(read(fd, (void *)&t, sizeof(t))){
				cout << t << " ,";
			}
			cout << " }";
		}else{
			int t;
			int fd = open(argv[3], O_RDWR);
			lseek(fd, (strtol(argv[2], NULL, 10) - 1) * sizeof(int), SEEK_CUR);
			read(fd, (void *)&t, sizeof(t));
			cout << "{ " << t << " }";
		}
	}

	
	return 0;
}