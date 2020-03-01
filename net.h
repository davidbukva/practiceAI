#ifndef NET_H
#define NET_J
#include "matrix.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

struct net{

	vector<matrix<double>> w;
    vector<vector<double>> b;

	int nlayers;
	vector<int> layers;

	net(std::initializer_list<int> _layers){
		srand(time(nullptr));
		nlayers = _layers.size();
		layers = _layers;
		w.init(nlayers);
		b.init(layers);
		for(int i = 1; i < nlayers; i++){
			w[i].init(layers[i],layers[i-1]);
		}
	}


	void calculategrad(const vector<vector<double>>& in, const vector<vector<double>> &des, vector<vector<vector<double>>> *nablaCW, vector<vector<double>> *nablaCB){
		for(int i = 1; i < nlayers; i++){
			(*nablaCB)[i].init(layers[i]);
			for(int j = 0; j < layers[i]; j++){
				(*nablaCW)[i][j].init(layers[i-1]);
			}
		}
	}


	void train(int epochs, double eta,const vector<vector<double>> &inputs, const vector<vector<double>> &desired, int minibsize){
		for(int epoch = 0; epoch < epochs; epoch++){

			//TODO: random shuffle
			
			
		}
	}


	double cost(vector<vector<double>> &inputs, vector<vector<double>> &desired){
		double sum = 0;
		for(int i = 0; i < inputs.size(); i++){
			sum += squarev(desired[i]-output(inputs[i]));
		}
		return sum/(2*inputs.size());
	}
		

	

	vector<double> output(vector<double> input){
		
		vector<double> a(layers[0]);
		a=input;
		for(int l = 1; l < nlayers; l++){
			a=sigmoid(w[l]*a+b[l]);
		}


		return a;

	}

	

	double sigmoid(double in){
		return 1.0/(1.0+exp(-in));
	}

	vector<double> sigmoid(vector<double> in){
		vector<double> ret;
		for(int i = 0; i < in.size(); i++){
			ret[i]=sigmoid(in[i]);
		}
		return ret;
	}

	vector<double> subv(vector<double> one, vector<double> two){
		vector<double> ans(one.size());
		for(int i = 0; i < one.size(); i++){
			ans[i]=one[i]-two[i];
		}
		return ans;
	}
	double squarev(vector<double> vec){
		double ans = 0;
		for(int i = 0; i < vec.size(); i++){
			ans += vec[i]*vec[i];
		}
		return ans;
	}



};
#endif //NET_H
