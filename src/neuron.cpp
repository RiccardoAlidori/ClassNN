//////////////////////////////////////////////////////////////
//  neuron.cpp                                              //
//  NeuralNetwork                                           //
//                                                          //
//  Created by Riccardo Alidori on 12/02/2020.              //
//  Copyright © 2019 Riccardo Alidori. All rights reserved. //
//                                                          //
//////////////////////////////////////////////////////////////
#include "include/neuron.hpp"

/* constructor */
Neuron::Neuron(){
	//cout << "new Neuron Created" << endl;
	double rndVal = ((double)rand())/((double)RAND_MAX);
	setVal(rndVal);
}

/* getter & setter */
double Neuron::getVal(){
	return this->val;
}
void Neuron::setVal(double x){
	this->val = x;
	setActivatedVal(x);
	setDerivatedVal(x);
}
double Neuron::getActivatedVal(){
	return this->activatedVal;
}
void Neuron::setActivatedVal(double x){
	/* Sigmoid Funcion*/
	this->activatedVal = 1 / (1 + exp(-x));
}
double Neuron::getDerivatedVal(){
	return this->derivatedVal;
}
void Neuron::setDerivatedVal(double x){
	this->derivatedVal = x * (1 - x);
}