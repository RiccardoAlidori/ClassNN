//////////////////////////////////////////////////////////////
//  neuron.hpp                                              //
//  NeuralNetwork                                           //
//                                                          //
//  Created by Riccardo Alidori on 12/02/2020.              //
//  Copyright © 2019 Riccardo Alidori. All rights reserved. //
//                                                          //
//////////////////////////////////////////////////////////////
#ifndef _NEURON_HPP_
#define _NEURON_HPP_

#include "config.hpp"
#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

class Neuron {
public:
	/* constructor */
	Neuron();	

	/* getter & setter */
	double getVal();
	void setVal(double x);
	double getActivatedVal();
	void setActivatedVal(double x);
	double getDerivatedVal();
	void setDerivatedVal(double x);
private:
	double val;
	double activatedVal;
	double derivatedVal;
};

#endif /* _NEURON_HPP_ */