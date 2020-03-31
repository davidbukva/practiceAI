#ifndef READMNIST_H
#define READMNIST_H

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include "mnist.h"
#include "matrix.h"

int readmnistdata(mnist *training_data, mnist *test_data, mnist *validation_data){
	int fd;
    unsigned char cnumImgs[4];
    int numImgs;

	if((fd = open("mnisttestlabels",O_RDONLY)) == -1)return -1;
    
    read(fd,cnumImgs,4);
    read(fd,cnumImgs,4);
    numImgs=cnumImgs[0]*(1<<24) + cnumImgs[1]*(1<<16) + cnumImgs[2]*(1<<8) + cnumImgs[3];
	test_data->init(numImgs);
	
    for(int i = 0; i < numImgs; i++){
		unsigned char label;
        if(read(fd,&label,1)==-1)return -1;
        for(int j = 0; j < 10; j++){
            test_data->labels[i][j]=0;
        }

        test_data->labels[i][label]=1;
    }


	if((fd = open("mnisttestimgs",O_RDONLY)) == -1)return -1;
	for(int i = 0; i < 4; i++)
		read(fd,cnumImgs,4);

	unsigned char *buf = new unsigned char[784*numImgs];
	read(fd,buf,784*numImgs);
	for(int i = 0; i < numImgs; i++){
		test_data->imgs[i].init(784,buf+784*i);
		test_data->imgs[i] /= 256;
	}
    delete buf;


	if((fd = open("mnisttrainlabels",O_RDONLY)) == -1)return -1;

	read(fd,cnumImgs,4);
	read(fd,cnumImgs,4);

    numImgs=cnumImgs[0]*(1<<24) + cnumImgs[1]*(1<<16) + cnumImgs[2]*(1<<8) + cnumImgs[3];
	training_data->init(numImgs);

	for(int i = 0; i < numImgs; i++){
		unsigned char label;
		if(read(fd,&label,1)==-1)return -1;
		for(int j = 0; j < 10; j++){
			training_data->labels[i][j]=0;
		}
		training_data->labels[i][label]=1;
	}


	if((fd = open("mnisttrainimgs",O_RDONLY)) == -1)return -1;
	for(int i = 0; i < 4; i++)
		read(fd,cnumImgs,4);

	buf = new unsigned char[784*numImgs];

	read(fd,buf,784*numImgs);
	for(int i = 0; i < numImgs; i++){
        
		training_data->imgs[i].init(784,buf+i*784);
		training_data->imgs[i] /= 256;
    }
    delete buf;
	
	
	

	close(fd);

	return 0;
	

}

#endif /* READMNIST_H */
