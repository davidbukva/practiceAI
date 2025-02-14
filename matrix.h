#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <iterator>
#include <cassert>

template <typename T>
struct matrix;

template <typename T>
struct vector{
    
    int n;
    
    std::unique_ptr<T[]> data;

    vector(const int _n){
        init(_n);
    }


	vector(const std::initializer_list<T>& sizes){
		init(sizes);
	}

    vector(const vector<T> &other){
        init(other);
    }

	vector(const int _n, const vector<int> &sizes){
		init(_n,sizes);
	}

    vector(const matrix<T>& other){
        assert(other.n==1 || other.m==1);
        if(other.n==1){
            init(other.m);
            for(int i = 0; i < n; i++){
                data[i]=other[0][i];
            }
        }else{
            init(other.n);
            for(int i = 0; i < n; i++){
                data[i]=other[i][0];
            }
        }
    }

    vector(){}

    vector<T>& init(const int _n){
        n=_n;
        data = std::make_unique<T[]>(std::size_t(n));
		return *this;
    }

	vector<T>& init(const std::initializer_list<T>& sizes){
		init(sizes.size());
		for(int i = 0; i < n; i++){
            data[i]=sizes.begin()[i];
		}
		return *this;
	}

	vector<T>& init(const vector<T>& other){
		init(other.size());
        for(int i = 0; i < n; i++)
            data[i]=other[i];
		return *this;
	}

	vector<T>& init(const int _n, const T& copy){
		init(_n);
		for(int i = 0; i < n; i++){
			data[i]=copy;
		}
		return *this;
	}

	vector<T>& init(const int _n, unsigned char* _data){
		init(_n);
		for(int i = 0; i < n; i++){
			data[i]=(T)_data[i];
		}
		return *this;
	}


    vector<T> operator-(const vector<T>& other) const{
        assert(n==other.n);
        vector<T> ret(other.size());
        for(int i = 0; i < n; i++){
            ret[i]=data[i]-other[i];
        }
        return ret;
    }
	

	vector<T> operator+(const vector<T>& other) const{
        assert(n==other.n);
		vector<T> ret(other.size());
		for(int i = 0; i < n; i++){
			ret[i] = data[i] + other[i];
		}
		return ret;
	}

	vector<T>& operator+=(const vector<T>& other) {
        assert(n==other.n);
		for(int i = 0; i < n; i++){
			data[i]+= other[i];
		}
		return *this;
	}

	T operator*(const vector<T>& rhs) const{
        assert(n==rhs.n);
		T ret(0);
		for(int i = 0; i < n; i++){
			ret+=data[i]*rhs[i];
		}
		return ret;
	}

	vector<T> operator*(const T& other) const{
		vector<T> ret(n);
		for(int i = 0; i < n; i++){
			ret[i]=data[i]*other;
		}
		return ret;
	}

	vector<T>& operator/(const T& rhs) const{
		vector<T> ret(n);
		for(int i = 0; i < n; i++){
			ret[i]=data[i]/rhs;
		}
		return ret;
	}

	vector<T>& operator/=(const T& rhs){
		for(int i = 0; i < n; i++){
			data[i] /= rhs;
		}
		return *this;
	}


    vector<T>& operator=(const vector<T>& other){
		init(other.size());
		for(int i = 0; i < n; i++){
			data[i]=other[i];
		}
        return *this;
    }

    vector<T>& operator=(std::initializer_list<T> other){
        init(other.size());
        for(int i = 0; i < n; i++){
            data[i]=other.begin()[i];
        }
        return *this;
    }

	vector<T>& operator=(T *other){
		for(int i = 0; i < n; i++){
			data[i]=other[i];
		}
		return *this;
	}

	vector<T> hadamard(const vector<T>& other){
        assert(n==other.n);
		vector<T> ret(n);
		for(int i = 0; i < n; i++){
			ret[i]=data[i]*other[i];
		}
		return ret;
	}

	int max(){
		int mx = 0;
		for(int i = 1; i < size(); i++){
			if(data[i]>data[mx])mx=i;
		}
		return mx;
	}

	vector<T>& operator=(double a){
		for(int i = 0; i < size(); i++)data[i]=a;
		return *this;
	}


    T& operator[](int pos) const{
        return data.get()[pos];
    }


    constexpr int size() const{
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
        data.init(n,vector<T>(m));
		return *this;
	}

    matrix(const vector<T>& vec){
        init(vec.n, 1);
        for(int i = 0; i < n; i++){
            data[i]=vec[i];
        }
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

    
	vector<T>& operator[](int pos) const{
		return data[pos];
	}

	vector<T> operator*(vector<T> rhs){
        assert(m==rhs.n);
		vector<T> ret(n);
		for(int k = 0; k < n; k++){
			ret[k] = data[k]*rhs;
		}
		return ret;
	}

    matrix<T> operator*(matrix<T> rhs){
        assert(m==rhs.n);
        matrix<T> ret(n,rhs.m);
        matrix<T> rtrans = rhs.transpose();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < rhs.m; j++){
                ret[i][j]=data[i]*rtrans[j];
            }
        }
        return ret;
    }


	constexpr int size() const{
		return n;
	}

	matrix<T>& operator=(const double a){
		for(int i = 0; i < size(); i++)
			data[i]=a;
		return *this;
	}

	matrix<T>& operator+=(const matrix<T>& other){
        assert(n==other.n);
        assert(m==other.m);
		for(int i = 0; i < n; i++)
			data[i]+=other[i];
		return *this;
	}

    matrix<T> transpose() const{
        matrix<T> ret(m, n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
                ret[j][i] = data[i][j];
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
