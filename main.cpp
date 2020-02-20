#include <iostream>
#include "matrix.h"
#include <string>
using namespace std;

int main(int nargs,char **args){
	int n,m;
	if(nargs<3){
		cerr << "Usage: " << args[0] << " " << "n m" << endl;
		return -1;
	}
	n = stoi(args[1]);
	m = stoi(args[2]);

	matrix m1(n,m);

	m1[0][0]=244;
	
	matrix mat(m1);
	mat.print();
	

}
