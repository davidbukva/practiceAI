#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <iostream>

template <typename T>
struct vector{
    
    int n;
    
    T *data;

    vector(int _n){
        init(_n);
    }

	vector(std::initializer_list<int> sizes){
		init(sizes);
	}

	vector(int _n, vector<int> sizes){
		init(_n,sizes);
	}

	vector(const vector<T>& other){
		(*this)=other;
	}

    vector(){}

    //vector(){}

    vector<T>& init(int _n){
        n=_n;
        data = (T *)malloc(n*sizeof(T));
		return *this;
    }

    vector<T>& init(std::initializer_list<int> sizes){
		init(sizes.size());
		for(int i = 0; i < n; i++){
			data[i].init(sizes[i]);
		}
		return *this;
	}

	vector<T>& init(int _n, vector<int> sizes){
		init(_n,sizes.data);
		return *this;
	}

	vector<T>& init(int _n, T copy){
		init(_n);
		for(int i = 0; i < n; i++){
			data[i]=copy;
		}
		return *this;
	}


    vector<T> operator-(vector<T> other){
        vector<T> ret(other.size());
        for(int i = 0; i < n; i++){
            ret[i]=data[i]-other[i];
        }
        return ret;
    }

	vector<T> operator+(vector<T> other){
		vector<T> ret(other.size());
		for(int i = 0; i < n; i++){
			ret[i] = data[i] + other[i];
		}
		return ret;
	}

	T operator*(vector<T> rhs){
		T ret;
		for(int i = 0; i < n; i++){
			ret+=data[i]*rhs[i];
		}
		return ret;
	}

	vector<T> operator*(T other){
		vector<T> ret(n);
		for(int i = 0; i < n; i++){
			ret[i]=data[i]*other;
		}
		return ret;
		
	}

    vector<T>& operator=(vector<T> other){
        init(n);
        for(int i = 0; i < n; i++){
            data[i]=other[i];
        }
        return *this;
    }

	vector<T>& operator=(T *other){
		for(int i = 0; i < n; i++){
			data[i]=other[i];
		}
		return *this;
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

    matrix(int _n, int _m){
        init(_n,_m);
    }

	matrix& init(int _n, int _m){
		n=_n;
		m=_m;
        data.init(n, vector<T>(m));
		return *this;
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
    
	vector<T>& operator[](int pos){
		return data[pos];
	}

	vector<T> operator*(vector<T> rhs){
		vector<T> ret(rhs.size());
		for(int k = 0; k < n; k++){
			ret[k] = data[k]*rhs;
		}
		return ret;
	}

	void print(){
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				std::cout << (int)data[j][i] << " ";
			}std::cout << "\n";
		}
	}




};


#endif /* MATRIX_H */
