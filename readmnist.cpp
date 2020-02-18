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
	for(int i = 0; i < 5; i++){
		((char *)(buf))[i]=0x00;
	}
	cout << "successful 1\n";
	fd = open("mnist",O_RDONLY);
	if(fd == -1)return -1;
	cout << "successful 2 " << fd << "\n";
	if(read(fd,buf,5)==-1)return -1;
	cout << "successful 3\n";
	cout << buf << endl;

	close(fd);


	return 0;
	

}

int main(){
	int ***training_data,***test_data, ***validation_data;

	readmnistdata(training_data, test_data, validation_data);

	return 0;
}
