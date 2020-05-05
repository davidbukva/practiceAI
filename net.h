#ifndef NET_H
#define NET_H

#include "matrix.h"
#include "mnist.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

struct net{

	vector<matrix<double>> w;
    vector<vector<double>> b;

	int nlayers;
	vector<int> layers;

	net(std::initializer_list<int> _layers){
		nlayers = _layers.size();
		layers = _layers;
		w.init(nlayers);
        b.init(nlayers);
		for(int i = 1; i < nlayers; i++){
			w[i].init(layers[i],layers[i-1]);
		    b[i].init(layers[i]);
		}
	}

	pair<vector<matrix<double>>,vector<vector<double>>> backprop(const vector<double>& input, const vector<double>& label){
	
        vector<double> a = input;
        vector<vector<double>> activations(nlayers);
        activations[0]=a;
        vector<vector<double>> zs(nlayers);
        for(int i = 1; i < nlayers; i++){
            vector<double> z = (w[i]*a)+b[i];
            zs[i]=z;
            a=sigmoid(z);
            activations[i]=a;
        }
        auto delta = cost_derivative(activations[nlayers-1],label).hadamard(sigmoid_prime(zs[nlayers-1]));
        
        vector<vector<double>> nabla_b(nlayers);
        vector<matrix<double>> nabla_w(nlayers);       
        
        for(int i = 1; i < nlayers; i++){
            nabla_w[i].init(layers[i],layers[i-1]);
            nabla_b[i].init(layers[i]);
        }

        nabla_b[nlayers-1] = delta;
        
        for(int i = 0; i < layers[nlayers-1]; i++){
            for(int j = 0; j < layers[nlayers-2]; j++){
                nabla_w[nlayers-1][i][j] = activations[nlayers-2][j]*delta[i];
            }
        }

        for(int l = nlayers-2; l >= 0; l--){
            delta = (w[l+1].transpose()*delta).hadamard(sigmoid_prime(zs[l]));
            
                       
            nabla_b[l] = delta;
            
            for(int i = 0; i < layers[l+1]; i++){
                for(int j = 0; j < layers[l]; j++){
                    nabla_w[l][i][j] = activations[l-1][j]*delta[i];
                }
            }

        }

        return {nabla_w,nabla_b};


	}

	void train(const int epochs, const double eta,const mnist& datain, const int minibsize){
		for(int epoch = 0; epoch < epochs; epoch++){

			vector<int> index(datain.size());
			for(int i = 0;i < index.size(); i++)index[i]=i;
			std::random_shuffle(index.data.get(),index.data.get()+index.size());
			mnist data(datain.size());
			for(int i = 0; i < data.size(); i++){
				data.imgs[i]=datain.imgs[index[i]];
				data.labels[i]=datain.labels[index[i]];
			}


			for(int batchnum = 0; batchnum+minibsize-1 < data.size(); batchnum+=minibsize){
				/*mnist minibatch(minibsize);*/
				/*for(int i = 0; i < minibsize; i++){*/
				/*minibatch.imgs[i]=data.imgs[batchnum+i];*/
				/*minibatch.labels[i]=data.labels[i];*/
				/*}*/
				vector<matrix<double>> nablaCW(w);
				vector<vector<double>> nablaCB(b);
				nablaCW = int(0);
				nablaCB = int(0);

				for(int i = 0; i < minibsize; i++){
					auto nabla = backprop(data.imgs[i+batchnum], data.labels[i+batchnum]);
					nablaCW+=nabla.first;
					nablaCB+=nabla.second;
				}
				for(int i = 0; i < w.size(); i++){
					for(int j = 0; j < w[i].size(); j++){
						for(int k = 0; k < w[i][j].size(); k++){
							w[i][j][k]=w[i][j][k]-(eta*nablaCW[i][j][k]/minibsize);
						}
					}
				}
				for(int i = 0; i < b.size(); i++){
					for(int j = 0; j < b[i].size(); j++){
						b[i][j]=b[i][j]-(eta*nablaCB[i][j]/minibsize);
					}
				}

			}

		}
	}


	double cost(const mnist& data) const{
		double sum = 0;
		for(int i = 0; i < data.imgs.size(); i++){
			sum += squarev(data.labels[i]-output(data.imgs[i]));
		}
		return sum/(2*data.imgs.size());
	}

	vector<double> cost_derivative(const vector<double>& output, const vector<double>& labels) const{
		return output-labels;
	}
		

	

	vector<double> output(const vector<double>& input) const{
		vector<double> a = input;
		for(int l = 1; l < nlayers; l++)
			a=sigmoid(w[l]*a+b[l]);
		
		return a;

	}

	int evaluate(const mnist& data) const{
		int good = 0;
		for(int i = 0; i < data.imgs.size(); i++){
			if(data.labels[i][output(data.imgs[i]).max()]==1)good++;
		}
		return good;
	}

    void randomize_weights(){
        std::srand(std::time(0));
        for(int i = 1; i < nlayers; i++){
            for(int j = 0; j < w[i].n; j++){
                for(int k = 0; k < w[i][j].size();k++)
				{
					w[i][j][k]=0.1*(std::rand()%10)-0.5;
				}	
            }
        }
    }

	

	constexpr double sigmoid(double in) const{
		return 1.0/(1.0+exp(-in));
	}

	constexpr double sigmoid_prime(double in) const{
		return sigmoid(in)*(1-sigmoid(in));
	}


	vector<double> sigmoid(const vector<double>& in) const{
		vector<double> ret(in.size());
		for(int i = 0; i < in.size(); i++){
			ret[i]=sigmoid(in[i]);
		}
		return ret;
	}

	double sigmoid_prime(const vector<double>& in) const{
		return sigmoid(in)*(sigmoid(in)-1)*-1;
	}

    vector<double> hadamard(const vector<double>& a, const vector<double>& b){
        vector<double> ret(a.size());
        for(int i = 0; i < a.size(); i++){
            ret[i]=a[i]*b[i];
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
