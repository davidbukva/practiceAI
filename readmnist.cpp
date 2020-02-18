#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int readmnistdata(int ***training_data, int ***test_data, int ***validation_data){
	int fd;
	char buf[5];


	if((fd = open("mnist",O_RDONLY)) == -1)return -1;

	if(read(fd,buf,5)==-1)return -1;

	cout << buf << endl;

	close(fd);


	return 0;
	

}

int main(){
	int ***training_data,***test_data, ***validation_data;

	readmnistdata(training_data, test_data, validation_data);

	return 0;
}
