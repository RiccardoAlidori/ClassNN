//////////////////////////////////////////////////////////////
//  main.cpp                                                //
//  NeuralNetwork                                           //
//                                                          //
//  Created by Riccardo Alidori on 12/02/2020.              //
//  Copyright © 2019 Riccardo Alidori. All rights reserved. //
//                                                          //
//////////////////////////////////////////////////////////////
#include <iostream>
#include "include/config.hpp"
#include "include/neuron.hpp"
#include "include/layer.hpp"
#include "include/net.hpp"

using namespace std;

int main(int argc, char*argv[]){
	vector<unsigned> topology = {256,16,16,10};

	Net *n = new Net(topology);
	n->loadTrainingSet("img");
	n->trainModel();
	n->plotGraph();
	cout << "bye!" << endl;	
	return 0;
} 