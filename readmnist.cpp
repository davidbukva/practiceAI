#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

int readmnistdata(pair<int **,int *> *training_data, pair<int **, int *> *test_data, pair<int **, int *> *validation_data){
	int fd;
    char cnumImgs[4];
    char label;
    int numImgs;
    int i,j;



	if((fd = open("mnisttestlabels",O_RDONLY)) == -1)return -1;
    
    read(fd,cnumImgs,4);
    read(fd,cnumImgs,4);

    numImgs=cnumImgs[0]*16*16*16*16*16*16 + cnumImgs[1]*16*16*16*16 + cnumImgs[2]*16*16 + cnumImgs[3];
    
    test_data = (pair<int **, int *> *)malloc(numImgs*794);

    for(i = 0; i < numImgs; i++){
        if(read(fd,&label,1)==-1)return -1;
        for(j = 0; j < 10; j++){
            test_data[i].second[j]=0;
        }
        test_data[i].second[label]=1;
    }
        

	close(fd);

	return 0;
	

}

int main(){
	pair<int **, int *> *training_data, *test_data, *validation_data;

	if(readmnistdata(training_data, test_data, validation_data)==-1){
        cerr << "Failed to read" << endl; 
        return -1;
    }
    for(int i = 0; i < 10; i++){
        cout << test_data[0].second[i] << " ";
    }cout << endl;
	return 0;
}
