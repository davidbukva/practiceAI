#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <iostream>

template <typename T>
struct vector{
    
    int n;
    
    T *data;

    vector(int _n):n(_n){
        data = (T *)malloc(n*sizeof(T));
    }

    vector(){}

    //vector(){}

    void init(int _n){
        n=_n;
        data = (T *)malloc(n*sizeof(T));
    }

    void init(int _n, T t){
        n=_n;
        data = (T *)malloc(n*sizeof(T));
        for(int i = 0; i < n; i++){
            data[i]=t;
        }
    }

    T& operator[](int pos){
        return data[pos];
    }

    int size(){
        return n;
    }
    



};

template <typename T>
struct matrix{

    int n;
    int m;

    vector<vector<T>> data;

    matrix(int _n, int _m): n(_n),m(_m){
        data.init(n, vector<T>(m));
    }

	void init(int _n, int _m){
		n=_n;
		m=_m;
        data = (T *)malloc(m*n);
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

	T& get(int pos){
		return operator[](pos);
	}
    
	T& operator[](int pos){
		return data[pos];
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
