#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

int readmnistdata(int **training_data, int **test_data, int **validation_data){
	int fd;
    char cnumImgs[4];
    char *buf;
    int numImgs;


	if((fd = open("mnist",O_RDONLY)) == -1)return -1;
    
    read(fd,cnumImgs,4);
    read(fd,cnumImgs,4);

    
    numImgs=cnumImgs[0]*16*16*16*16*16*16 + cnumImgs[1]*16*16*16*16 + cnumImgs[2]*16*16 + cnumImgs[3];

    buf=(char *)malloc(numImgs);

	if(read(fd,buf,numImgs)==-1)return -1;
    cout << (int)buf[0] << endl;
        
	close(fd);
    free(buf);

	return 0;
	

}

int main(){
	int **training_data,**test_data, **validation_data;

	readmnistdata(training_data, test_data, validation_data);

	return 0;
}
