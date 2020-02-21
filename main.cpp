#include <iostream>
#include <string>


#include "matrix.h"
#include "readmnist.h"

using namespace std;

int main(){
	

	mnist training_data, test_data, validation_data;
	if(readmnistdata(&training_data, &test_data, &validation_data)==-1){
        cerr << "Failed to read" << endl; 
        return -1;
    }
	

	//cout << test_data->numData << endl;
	//cout << test_data.numData << endl;
	//for(int i = 0; i < 10; i++){
	//cout << test_data->labels[0] << endl;
	//}
	

	
	

}
