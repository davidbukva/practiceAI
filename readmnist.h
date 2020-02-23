#ifndef READMNIST_H
#define READMNIST_H

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include "matrix.h"


struct mnist{

	int numData;

	matrix *imgs;
	matrix *labels;

	void init(int _numData){
		
		numData = _numData;

		imgs = (matrix *)malloc(_numData*sizeof(matrix));
		labels = (matrix *)malloc(_numData*sizeof(matrix));

		for(int i = 0; i < _numData; i++){
			imgs[i].init(1,784);
			labels[i].init(1,10);
		}
	}


	
	~mnist(){
		free(imgs);
		free(labels);
	}
};


int readmnistdata(mnist *training_data, mnist *test_data, mnist *validation_data){
	int fd;
    unsigned char cnumImgs[4];
    unsigned int numImgs;

	if((fd = open("mnisttestlabels",O_RDONLY)) == -1)return -1;
    
    read(fd,cnumImgs,4);
    read(fd,cnumImgs,4);
    numImgs=cnumImgs[0]*(1<<24) + cnumImgs[1]*(1<<16) + cnumImgs[2]*(1<<8) + cnumImgs[3];
	test_data->init(numImgs);
	
    for(int i = 0; i < numImgs; i++){
		unsigned char label;
        if(read(fd,&label,1)==-1)return -1;
        for(int j = 0; j < 10; j++){
            test_data->labels[i][j][0]=0;
        }

        test_data->labels[i][label][0]=1;
    }


	if((fd = open("mnisttestimgs",O_RDONLY)) == -1)return -1;
	for(int i = 0; i < 4; i++)
		read(fd,cnumImgs,4);

    for(int i = 0; i < numImgs; i++){
		read(fd,test_data->imgs[i].data,784);
	}



	if((fd = open("mnisttrainlabels",O_RDONLY)) == -1)return -1;

	read(fd,cnumImgs,4);
	read(fd,cnumImgs,4);

    numImgs=cnumImgs[0]*(1<<24) + cnumImgs[1]*(1<<16) + cnumImgs[2]*(1<<8) + cnumImgs[3];
	training_data->init(numImgs);

	for(int i = 0; i < numImgs; i++){
		unsigned char label;
		if(read(fd,&label,1)==-1)return -1;
		for(int j = 0; j < 10; j++){
			training_data->labels[i][j][0]=0;
		}
		training_data->labels[i][label][0]=1;
	}

	if((fd = open("mnisttrainimgs",O_RDONLY)) == -1)return -1;
	for(int i = 0; i < 4; i++)
		read(fd,cnumImgs,4);

    for(int i = 0; i < numImgs; i++){
		read(fd,training_data->imgs[i].data,784);
	}
	
	

	close(fd);

	return 0;
	

}

#endif /* READMNIST_H */
