#ifndef NET_H
#define NET_J
#include "matrix.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

struct net{

	vector<matrix<double>> w;
    matrix<double> b;

	int nlayers;
	vector<int> layers;

	net(int _nlayers, int *_layers){
		srand(time(nullptr));
		nlayers = _nlayers;
		layers.init(nlayers);
		w.init(nlayers);
		b.init(nlayers, _layers);
		for(int i = 1; i < nlayers; i++){
			b[i].init(layers[i]);
			w[i].init(layers[i]);
			for(int j = 0; j < layers[i]; j++){
				w[i][j].init(layers[i-1]);
				for(int k = 0; k < layers[i-1];k++){
					double num = (rand()%10-5);
					if(num == 0)num++;
					w[i][j][k]=1.0/num;
				}
			}
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

			cout << "epoch start: " << epoch << endl;
			//TODO: random shuffle
			
			vector<vector<vector<double>>> nablaCW(w.size());
			vector<vector<double>> nablaCB(b.size());

			for(int minibi = 0; minibi < inputs.size()-minibsize; minibi+=minibsize){		

				vector<vector<vector<double>>> nablaCWx(w.size());
				vector<vector<double>> nablaCBx(b.size());
				vector<vector<double>> in(minibsize);
				vector<vector<double>> des(minibsize);

				for(int minibj = 0; minibj < minibsize; minibj++){
					in[minibj]=inputs[minibi+minibj];
					des[minibj]=desired[minibi+minibj];
				}
				
				calculategrad(in,des,&nablaCW,&nablaCB);


			for(int i = 1; i < nlayers; i++){
				for(int j = 0; j < layers[i]; j++){
					nablaCB[i][j]+=nablaCBx[i][j];
					for(int k = 0; k < layers[i-1]; k++){
						nablaCW[i][j][k]+=nablaCWx[i][j][k];
					}
				}
			}

			}
			for(int i = 1; i < nlayers; i++){
				for(int j = 0; j < layers[i]; j++){
					b[i][j]-=eta*nablaCB[i][j];
					for(int k = 0; k < layers[i-1]; k++){
						w[i][j][k]-=eta*nablaCW[i][j][k];
					}
				}
			}
		}
	}


	double cost(vector<vector<double>> &inputs, vector<vector<double>> &desired){
		double sum = 0;
		for(int i = 0; i < inputs.size(); i++){
			sum += squarev(desired[i]-output(inputs[i]));
		}
		sum/=2*inputs.size();
		return sum;
	}
		

	

	vector<double> output(const vector<double> &input){
		
		vector<vector<double>> vals(nlayers);
		/*vals[0]=input;*/
		vals[0].init(input.size());
		for(int j = 0; j < input.size(); j++){
			vals[0][j]=input[j];
		}
		for(int i = 1; i < nlayers; i++){
		vals[i].init(layers[i]);
			for(int j = 0; j < layers[i]; j++){
				vals[i][j]=b[i][j];
				for(int k = 0; k < layers[i-1]; k++){
					vals[i][j]+=vals[i-1][k]*w[i][j][k];
				}
				vals[i][j]=sigmoid(vals[i][j]);
			}
		}

		return vals[nlayers-1];

	}


	double sigmoid(double in){
		return 1.0/(1.0+exp(-in));
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
