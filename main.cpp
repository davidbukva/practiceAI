#include <iostream>
#include <string>


#include "matrix.h"
#include "readmnist.h"

using namespace std;

int main(){
	
	mnist *training_data = (mnist *)malloc(sizeof(mnist));
	mnist *test_data = (mnist *)malloc(sizeof(mnist));
	mnist *validation_data = (mnist *)malloc(sizeof(mnist));
	if(readmnistdata(training_data, test_data, validation_data)==-1){
		cerr << "Failed to read" << endl; 
		return -1;
	}

}
