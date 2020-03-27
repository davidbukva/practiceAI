using namespace std;
#include <iostream>
#include <string>
#include <cstring>
#include <memory>
#include <cstdlib>

#include "matrix.h"
#include "readmnist.h"
#include "net.h"



int main(){
	
    std::srand(std::time(nullptr));

	//mnist *training_data = (mnist *)malloc(sizeof(mnist));
	//mnist *test_data = (mnist *)malloc(sizeof(mnist));
	//mnist *validation_data = (mnist *)malloc(sizeof(mnist));

    mnist training_data,test_data,validation_data;
	if(readmnistdata(&training_data, &test_data, &validation_data)==-1){
		cerr << "Failed to read" << endl; 
		return -1;
	}
    cout << "read data\n";
    cout.flush();
	

	net nn({784,30,10});
    nn.randomize_weights();
    cout << nn.output(training_data.imgs[12])[0] << endl;

}
