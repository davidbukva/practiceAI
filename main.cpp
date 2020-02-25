using namespace std;
#include <iostream>
#include <string>

#include "matrix.h"
#include "readmnist.h"
//#include "net.h"


int main(){
	
	//mnist *training_data = (mnist *)malloc(sizeof(mnist));
	//mnist *test_data = (mnist *)malloc(sizeof(mnist));
	//mnist *validation_data = (mnist *)malloc(sizeof(mnist));

    mnist training_data,test_data,validation_data;

	if(readmnistdata(&training_data, &test_data, &validation_data)==-1){
		cerr << "Failed to read" << endl; 
		return -1;
	}
	
    matrix<int> m(2,2);
    m.print();
    m[1][0]=2;
    m.print();    


}
