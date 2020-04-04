#ifndef MNIST_H
#define MNIST_H

#include "matrix.h"

struct mnist{

	int numData;

	vector<vector<double>> imgs;
	vector<vector<double>> labels;
	
	mnist() = default;
	mnist(int _numData){
		init(_numData);
	}

	void init(int _numData){
		
		numData = _numData;

        imgs.init(_numData);
        labels.init(_numData);

		for(int i = 0; i < _numData; i++){
			imgs[i].init(784);
			labels[i].init(10);
		}
	}

	constexpr int size() const{
		return numData;
	}

	
};

#endif //MNIST_H
