#include <iostream>

#include "matrix.h"
#include "mnist.h"
#include "readmnist.h"
#include "net.h"

#include <iomanip>
using namespace std;

int main(){

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
    //cout << training_data.imgs.size();
    //cout << endl << training_data.imgs[0].size()  << endl;
    //cout << nn.cost(training_data.imgs,training_data.labels) << endl;
    
    if(test_data.size() > 0){
        int good = 0;
        for(int i = 0; i < test_data.size(); i++){
            if(test_data.labels[i][nn.output(test_data.imgs[i]).max()]==1)
                good++;
        }
        std::cout << "evaluated: " << good << "/" << test_data.size();
    }
    std::cout << std::endl;
    
    nn.train(20, 3, training_data, 10, test_data);
    

}
