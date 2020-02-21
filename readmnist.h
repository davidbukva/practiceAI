#ifndef READMNIST_H
#define READMNIST_H

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"


struct mnist{

	int numData;

	matrix **imgs;
	matrix **labels;

	void init(int _numData){
		
		numData = _numData;

		imgs = (matrix **)malloc(_numData*sizeof(matrix *));
		labels = (matrix **)malloc(_numData*sizeof(matrix *));

		for(int i = 0; i < _numData; i++){
			imgs[i] = new matrix(28,28);
			labels[i] = new matrix(1,10);
		}
	}


	
	~mnist(){
		free(imgs);
		free(labels);
		std::cout << "destructed mnist" << std::endl;
	}
};


int readmnistdata(mnist &training_data, mnist &test_data, mnist &validation_data){
	int fd;
    char cnumImgs[4];
    int numImgs;

	if((fd = open("mnisttestlabels",O_RDONLY)) == -1)return -1;
    
    read(fd,cnumImgs,4);
    read(fd,cnumImgs,4);
    numImgs=cnumImgs[0]<<24 + cnumImgs[1]<<16 + cnumImgs[2]<<8 + cnumImgs[3];
    
	test_data->init(numImgs);
	/*std::cout << test_data->numData << std::endl;*/
	std::cout << test_data << std::endl;
    for(int i = 0; i < numImgs; i++){
		char label;
        if(read(fd,&label,1)==-1)return -1;
        for(int j = 0; j < 10; j++){
            (*test_data->labels[i])[0][0]=0;
        }

        (*test_data->labels[i])[label][0]=1;
    }
        

	close(fd);

	return 0;
	

}

#endif /* READMNIST_H */
