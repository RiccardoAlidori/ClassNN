//////////////////////////////////////////////////////////////
//  layer.cpp                                               //
//  NeuralNetwork                                           //
//                                                          //
//  Created by Riccardo Alidori on 12/02/2020.              //
//  Copyright © 2019 Riccardo Alidori. All rights reserved. //
//                                                          //
//////////////////////////////////////////////////////////////
#include "include/layer.hpp"

/* constructor */
Layer::Layer(unsigned size, unsigned prevLayerSize){
	//cout << "new Layer Created" << endl;
	this->layerSize = size;
	this->prevLayerSize = prevLayerSize;
	vector<double> rndVal;
	for (unsigned i=0; i < size; i++){	
		//Neuron n;
		Neuron *n = new Neuron;
		this->neurons.push_back(n);
		// bias
		rndVal.push_back(((double)rand())/((double)RAND_MAX));
	}	
	setBias(rndVal);
	//weights
	this->weights.resize(size);
	for (unsigned i=0; i< size; i++)
		this->weights.at(i).resize(this->prevLayerSize);
	/* foreach neuron, fill a vector of random weights equal
	to the number of neuron of the previous layer
	each layer has a matrix of weights*/
	for (unsigned i=0; i < size; i++){	
		for (unsigned j=0; j< this->prevLayerSize;j++){
			setWeight(i,j,((double)rand())/((double)RAND_MAX));
		}
	}
	this->deltaError.resize(size);
}

void Layer::forward(Layer previousLayer){
	// A[L] = f(W[L]*A[L-1] + b[L])
	/* foreach neuron in the current layer */
	for (unsigned i = 0; i < this->layerSize; i++){
		double activation = this->bias.at(i);
		/* foreach neuron of the previous layer, multipy it
		   by the weight of the current layer */
		for (unsigned j = 0; j < this->prevLayerSize;j++){
			activation += previousLayer.getNeuron(j).getVal()*getWeight(i,j);
		}
		this->neurons.at(i)->setVal(activation);
		this->neurons.at(i)->setVal(this->neurons.at(i)->getActivatedVal());
		
	}	
}

void Layer::backprop(Layer previousLayer){
	/* Update the weights & bias */
	for (unsigned i = 0; i < this->layerSize; i++){
		this->bias.at(i) += this->deltaError.at(i)*LR;
		for (unsigned j = 0; j < this->prevLayerSize; j++){
			// Weights+=perviousLayer*deltaError*LR;
			this->setWeight(i,j, (this->getWeight(i,j)+previousLayer.getNeuron(j).getVal()*this->deltaError.at(i)*LR));
		}
	}
}

void Layer::computeDError(Layer followingLayer){
	/* compute the deltaError, based on the previous layer Weights and deltaError */	
	for (unsigned i = 0; i < this->layerSize; i++){
		double error = 0;
		for (unsigned j = 0; j < followingLayer.getLayerSize(); j++){
			error += followingLayer.getDeltaError().at(j)*followingLayer.getWeight(j,i);
		}
		this->deltaError.at(i) = error * this->neurons.at(i)->getDerivatedVal();
	}
}

void Layer::printWeights(){
	for (unsigned i = 0; i < this->layerSize; i++){
		cout <<"\t\t";
		for (unsigned j = 0; j < this->prevLayerSize; j++){
			cout <<getWeight(i,j) << " " ;
		}
		cout << endl;
	}
}

/* getter & setter */

Neuron &Layer::getNeuron(unsigned pos){
	return *this->neurons.at(pos);
}

void Layer::setLayer(/*todo*/){

}
double Layer::getWeight(unsigned row, unsigned col){
	return this->weights.at(row).at(col);
}
void Layer::setWeight(unsigned row, unsigned col,double x){
	this->weights.at(row).at(col) = x;
}
vector<double> Layer::getBias(){
	return this->bias;
}
void Layer::setBias(vector<double> x){
	this->bias = x;
}
unsigned Layer::getLayerSize(){
	return this->layerSize;
}
void Layer::setDeltaError(vector<double> dError){
	for (unsigned i = 0; i < dError.size(); ++i){
		this->deltaError.at(i) = dError.at(i);
	}
}
vector<double> Layer::getDeltaError(){
	return this->deltaError;
}