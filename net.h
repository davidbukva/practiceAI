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
        b.init(nlayers);
		for(int i = 1; i < nlayers; i++){
			w[i].init(layers[i],layers[i-1]);
		    b[i].init(layers[i]);
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


	double cost(const vector<vector<double>> &inputs, const vector<vector<double>> &desired) const{
		double sum = 0;
		for(int i = 0; i < inputs.size(); i++){
			sum += squarev(desired[i]-output(inputs[i]));
		}
		return sum/(2*inputs.size());
	}
		

	

	vector<double> output(const vector<double>& input) const{
		
		vector<double> a(layers[0]);
		a=input;
		for(int l = 1; l < nlayers; l++){
			a=sigmoid(w[l]*a+b[l]);
		}


		return a;

	}

    void randomize_weights(){
        std::srand(std::time(0));
        for(int i = 1; i < nlayers; i++){
            for(int j = 0; j < w[i].n; j++){
                for(int k = 0; k < w[i][j].size();k++)
                    w[i][j][k]=0.1*(std::rand()%10);
            }
        }
    }

	

	constexpr double sigmoid(double in) const{
		return 1.0/(1.0+exp(-in));
	}

	vector<double> sigmoid(const vector<double>& in) const{
		vector<double> ret(in.size());
		for(int i = 0; i < in.size(); i++){
			ret[i]=sigmoid(in[i]);
		}
		return ret;
	}

	vector<double> subv(const vector<double>& one, const vector<double>& two) const{
		vector<double> ans(one.size());
		for(int i = 0; i < one.size(); i++){
			ans[i]=one[i]-two[i];
		}
		return ans;
	}
	double squarev(const vector<double>& vec) const{
		double ans = 0;
		for(int i = 0; i < vec.size(); i++){
			ans += vec[i]*vec[i];
		}
		return ans;
	}



};
#endif //NET_H
