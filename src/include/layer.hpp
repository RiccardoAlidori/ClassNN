//////////////////////////////////////////////////////////////
//  layer.hpp                                               //
//  NeuralNetwork                                           //
//                                                          //
//  Created by Riccardo Alidori on 12/02/2020.              //
//  Copyright © 2019 Riccardo Alidori. All rights reserved. //
//                                                          //
//////////////////////////////////////////////////////////////
#ifndef _LAYER_HPP_
#define _LAYER_HPP_

#include "neuron.hpp"
#include "config.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;


class Layer {
public:
	/* constructor */
	Layer(unsigned size, unsigned prevLayerSize);

	void forward(Layer previousLayer);
	void backprop(Layer previousLayer);
	void computeDError(Layer followingLayer);

	/* getter & setter */
	Neuron &getNeuron(unsigned pos);
	void setLayer(/*todo*/);
	double getWeight(unsigned row, unsigned col);
	void setWeight(unsigned row, unsigned col,double x);
	vector<double> getBias();
	void setBias(vector<double> x);
	unsigned getLayerSize();
	void setDeltaError(vector<double> dError);
	vector<double> getDeltaError();
	void printWeights();
private:
	vector<Neuron*> neurons;
	vector<vector<double>> weights;
	vector<double> bias;
	vector<double> deltaError;
	unsigned layerSize;
	unsigned prevLayerSize;
};

#endif /* _LAYER_HPP_*/