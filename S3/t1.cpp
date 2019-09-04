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
	for (int i = 1; i < argc; ++i)
	{
		//argv[i];
		//cout << argv[i];
		if(!strcmp(argv[i] , "-c")){
			mkdir(argv[i + 2], strtol(argv[i + 1], NULL , 8));
		}
		if(!strcmp(argv[i] , "-w")){
			string data;
			cin >> data;
			char dataSt[data.size() + 1];
			for (int i = 0; i < data.size(); ++i)
			{
				dataSt[i] = data[i];
				
			}
			dataSt[data.size()] = '\0';
			int fd = open(argv[i + 1], O_RDWR | O_CREAT, 00755);
			write(fd, (void *)dataSt, data.size());
		}
		if(!strcmp(argv[i] , "-r")){
			int fd = open(argv[i + 1], O_RDWR | O_CREAT, 00755);
			char buffer[255];
			while(read(fd, (void *)buffer, 255) > 0){
				cout << buffer;
			}
		}

	}
	return 0;
}