#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <iostream>


struct matrix{

    int n;
    int m;

    unsigned char *data;

    matrix(int _n, int _m): n(_n),m(_m){
        data = (unsigned char *)malloc(m*n);
    }

	void init(int _n, int _m){
		n=_n;
		m=_m;
        data = (unsigned char *)malloc(m*n);
	}

	matrix(){
		
	}

	/*matrix(const matrix &mat){*/
	/*matrix(mat.n,mat.m,mat.data);*/
	/*}*/

	/*matrix(int _n, int _m, int **_data): n(_n), m(_m){*/
	/*data = (int **)malloc(m*sizeof(int *));*/
	/*for(int i = 0; i < m; i++){*/
	/*data[i] = (int *)malloc(n*sizeof(int));*/
	/*for(int j = 0; j < n; j++){*/
	/*data[i][j]=_data[i][j];*/
	/*}*/
	/*}*/
	/*}*/

	unsigned char *get(int pos){
		return operator[](pos);
	}
    
	unsigned char *operator[](int pos){
		return (data+pos*n);
	}

	void print(){
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
			int ind = i*n+j;
				std::cout << (int)data[ind] << " ";
			}std::cout << "\n";
		}
	}

	~matrix(){
		free(data);
	}



};

#endif /* MATRIX_H */
