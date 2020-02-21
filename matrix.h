#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <iostream>


struct matrix{

    int n;
    int m;

    int **data;

    matrix(int _n, int _m): n(_n),m(_m){
        data = (int **)malloc(m*sizeof(int *));
		for(int i = 0; i < m; i++){
			data[i] = (int *)malloc(n*sizeof(int));
			for(int j = 0; j < n; j++){
				data[i][j]=0;
			}
		}
    }

	matrix(){
		
	}

	/*matrix(const matrix &mat){*/
	/*matrix(mat.n,mat.m,mat.data);*/
	/*}*/

	matrix(int _n, int _m, int **_data): n(_n), m(_m){
		data = (int **)malloc(m*sizeof(int *));
		for(int i = 0; i < m; i++){
			data[i] = (int *)malloc(n*sizeof(int));
			for(int j = 0; j < n; j++){
				data[i][j]=_data[i][j];
			}
		}
	}

	int *get(int pos){
		return operator[](pos);
	}
    
	int *operator[](int pos){
		return data[pos];
	}

	void print(){
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				std::cout << data[i][j] << " ";
			}std::cout << "\n";
		}
	}

	~matrix(){
		free(data);
	}



};

#endif /* MATRIX_H */
