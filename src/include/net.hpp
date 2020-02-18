//////////////////////////////////////////////////////////////
//  net.hpp                                                 //
//  NeuralNetwork                                           //
//                                                          //
//  Created by Riccardo Alidori on 12/02/2020.              //
//  Copyright © 2019 Riccardo Alidori. All rights reserved. //
//                                                          //
//////////////////////////////////////////////////////////////
#ifndef _NET_HPP_
#define _NET_HPP_

#include "layer.hpp"
#include "config.hpp"
#include "matplotlib-cpp/matplotlibcpp.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <ctime>

namespace plt = matplotlibcpp;
using namespace std;


class Net {
public:
/* constructor */
Net(vector<unsigned> topology);	

int trainModel();
void error(); 
void printNet(bool withWeights);
void printTrainMatrix();
int loadTrainingSet(string filename);
void plotGraph();
/* getter & setter */

private:
	void setInputTrainVal(vector<double> inVal);
	void setOutputTrainVal(vector<double> outVal);
	void forward();
	void backprop();
	vector<Layer*> layers;
	unsigned numLayer;
	vector<vector<double>> weights;
	vector<vector<double>> trainInMatrix;
	vector<vector<double>> trainOutMatrix;
	vector<double> currentTrainIn;
	vector<double> currentTrainOut;
	//vector<double> deltaError;
	vector<unsigned> trainingSetOrder;
  	vector<double> graphErr;	// y valye of the graph
	vector<double> graphXval;	// x value of the graph
	double tmpErr,tmpErr1;		// temporary error from Output layer
};

#endif /* _NET_HPP_ */