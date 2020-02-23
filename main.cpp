
using namespace std;
#include <iostream>
#include <string>
#include <bits/stdc++.h>

#include "matrix.h"
#include "readmnist.h"
#include "net.h"


int main(){
	
	mnist *training_data = (mnist *)malloc(sizeof(mnist));
	mnist *test_data = (mnist *)malloc(sizeof(mnist));
	mnist *validation_data = (mnist *)malloc(sizeof(mnist));
	if(readmnistdata(training_data, test_data, validation_data)==-1){
		cerr << "Failed to read" << endl; 
		return -1;
	}
	

	vector<int> layers(3);
	layers[0]=784;
	layers[1]=50;
	layers[2]=10;
	
	int train = training_data->numData;
	vector<vector<double>> input(train);
	vector<vector<double>> desired(train);
	
	for(int i = 0; i < train; i++){
		input[i].resize(784);
		desired[i].resize(10);
		for(int j = 0; j < 10; j++){
			desired[i][j]=(double)training_data->labels[i].data[j];
		}
		for(int j = 0; j < 784; j++){
			input[i][j]=(double)training_data->imgs[i].data[j];
		}
	}

	net nn(layers);

	nn.train(10,1.0,input,desired,10);
}
