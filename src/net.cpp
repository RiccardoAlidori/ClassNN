//////////////////////////////////////////////////////////////
//  net.cpp                                                 //
//  NeuralNetwork                                           //
//                                                          //
//  Created by Riccardo Alidori on 12/02/2020.              //
//  Copyright © 2019 Riccardo Alidori. All rights reserved. //
//                                                          //
//////////////////////////////////////////////////////////////
#include "include/net.hpp"

/* constructor */
Net::Net(vector<unsigned> topology){
	//cout << "new Network Created" << endl;
	this->numLayer = topology.size();
	// Input Layer
	/* Previous layer Size = 0*/
	Layer *l = new Layer(topology.at(0),0);
	//Layer l(topology.at(0), 0);			
	this->layers.push_back(l);	
	for (unsigned i = 1; i < this->numLayer; i++){
		//Layer l(topology.at(i), topology.at(i-1));
		Layer *l = new Layer(topology.at(i), topology.at(i-1));
		this->layers.push_back(l);	
	}
}	

int Net::trainModel(){
	// current date/time based on current system
 	time_t now = time(0);
 	// convert now to string form
 	char* dt = ctime(&now);
 	cout << "Training is started at " << dt << endl;
 	clock_t begin = clock();
	for (int n=0; n < EPOCHS; n++) {
		cout << "[+] Train_model : "<<100*(n+1)/EPOCHS <<"%\r";
		cout.flush();
		// shuffling input 
		random_shuffle(trainingSetOrder.begin(), trainingSetOrder.end());

	    this->tmpErr=0;
		for(unsigned i = 0; i < trainingSetOrder.size(); i++){
			setInputTrainVal(trainInMatrix.at(trainingSetOrder.at(i)));
			setOutputTrainVal(trainOutMatrix.at(trainingSetOrder.at(i)));		

			forward();

			// at last iteration, print out the results
			if(n==EPOCHS-1){ 
	      		cout << endl;	
	        	cout << "Input: ";
	       		for (unsigned j=0; j< this->layers.at(0)->getLayerSize(); j++){
	       			cout << trainInMatrix.at(trainingSetOrder.at(i)).at(j) << " ";
	   			}
			    cout << "\tOutput: ";
			    for (unsigned j=0; j< this->layers.at(numLayer-1)->getLayerSize(); j++){
	           		cout << this->layers.at(numLayer-1)->getNeuron(j).getVal() << " ";
			    }
			    cout << "\tExpected Output: ";
			    for (unsigned j=0; j< this->layers.at(numLayer-1)->getLayerSize(); j++){
	           		cout << trainOutMatrix.at(trainingSetOrder.at(i)).at(j) << " ";
			    }
			    cout << endl;
			}
      		this->tmpErr1 = 0;
			backprop();	

			// compute the output layer mean error
			this->tmpErr1 /= this->layers.at(numLayer-1)->getLayerSize(); 
      		this->tmpErr += this->tmpErr1;

		}
		// store the error each 50 epochs
   		this->tmpErr /= trainingSetOrder.size();		
		if (n%50){
	      this->graphErr.push_back(this->tmpErr); 
	      this->graphXval.push_back(n);
	    } 
	}
	cout << endl;
  	cout << "[+] Train_model : Done"<< endl << endl;	
  	// current date/time based on current system
 	now = time(0);
 	// convert now to string form
 	dt = ctime(&now);
 	cout << "Training done at " << dt;
 	clock_t end = clock();
 	cout << "Elapsed time " << double(end - begin) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}
 
void Net::forward(){
	for (unsigned i = 1; i < this->numLayer; i++){
		// forwarding function of a layer (layers.at(i)), passing the previous one (layers.at(i-1))
		this->layers.at(i)->forward(*this->layers.at(i-1));
	}
}
void Net::backprop(){
	/* computing first the Error at output layer:
	set the delta Error Of the last layer as the
    one computed based on the Training output */
	vector<double> dError;
	dError.resize(this->layers.at(this->numLayer-1)->getLayerSize());
	for (unsigned i = 0; i < this->layers.at(this->numLayer-1)->getLayerSize(); i++){
		double error = this->currentTrainOut.at(i) - this->layers.at(this->numLayer-1)->getNeuron(i).getVal();
		dError.at(i) = error * this->layers.at(this->numLayer-1)->getNeuron(i).getDerivatedVal();
		this->tmpErr1 += abs(error);
	}
	this->layers.at(this->numLayer-1)->setDeltaError(dError);

	/* compute the hidden layers deltaError*/
	for (unsigned i = this->numLayer-1; i --> 0;){
		this->layers.at(i)->computeDError(*this->layers.at(i+1));
	}

	/* backpropagate until the first hidden layer */
	for (unsigned i = this->numLayer; i --> 1;){
		// backpropagation function of a layer (layers.at(i)), passing the previous one (layers.at(i-1)))
		this->layers.at(i)->backprop(*this->layers.at(i-1));
	}
}

void Net::error(){
/*
	vector<double> dError;
	for (unsigned i = 0; i < this->layers.at(this->numLayer-1)->getLayerSize(); i++){
		double error = this->currentTrainOut.at(i) - this->layers.at(this->numLayer-1)->getNeuron(i).getVal();
		this->dError.at(i) = error * this->layers.at(this->numLayer-1)->getNeuron(i).getDerivatedVal();
	}
	this->layers.at(this->numLayer-1)->setDeltaError(dError);
*/
}

void Net::printNet(bool withWeights){
	for (unsigned i = 0; i < this->numLayer; i++){
		cout << "Layer " << i << endl;
		if(i && withWeights){
			cout << "\tWeights " << endl;
			this->layers.at(i)->printWeights();
		}
		cout << "\tNeurons"<< endl;
		cout << "\t\t" ;
		for (unsigned j = 0; j < this->layers.at(i)->getLayerSize(); j++){
			cout << this->layers.at(i)->getNeuron(j).getVal() << " ";
		}
		cout << endl;
		cout <<"-------------------------"<< endl;
	}
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}
void Net::setInputTrainVal(vector<double> inVal){
	if (inVal.size() == this->layers.at(0)->getLayerSize()){
		// save in currentTrainIn the training input vector
		this->currentTrainIn = inVal;
		// copy the training input vector to the input layer
		for (unsigned i = 0; i < this->layers.at(0)->getLayerSize(); i++){
			this->layers.at(0)->getNeuron(i).setVal(this->currentTrainIn.at(i));
		}
	} else {
		cout << "input values don't match input Layer size" << endl;
	}
}
void Net::setOutputTrainVal(vector<double> outVal){
	if (outVal.size() == this->layers.at(this->numLayer-1)->getLayerSize()){
		// save in currentTrainOut the training out vector
		this->currentTrainOut = outVal;
		//this->deltaError.resize(outVal.size());
	} else {
		cout << "output values don't match output Layer size" << endl;
	}	
}

int Net::loadTrainingSet(string filename){
	string pathIn = "data/training/train_in_";
	string pathOut = "data/training/train_res_";
	string extension = ".txt";  
	std::string delimiter = " ";
   	int pos;

	/* Parse Training Inputs */
	string path = pathIn;
	path.append(filename);
	path.append(extension);
	//cout << path << endl;

	string line;
	int rows=0,cols=0;
    /* INPUT TRAINING MATRIX */
	ifstream f_in (path);
	if (f_in.is_open()){
		while (getline(f_in,line)){
			this->trainingSetOrder.push_back(rows);
			// trim leading spaces
			line.erase(line.find_last_not_of(" \n\r\t")+1);
			trainInMatrix.resize(rows+1);
			pos = line.find(delimiter);
			if(pos<0){
				// in case train matrix is a single column
				pos=1;
			}			
			while(line.length()){
				trainInMatrix.at(rows).resize(cols+1);
	       		string token = line.substr(0, pos);
	       		double x = stoi(token, 0, 16);
	       		trainInMatrix.at(rows).at(cols) = x;
	       		line.erase(0, pos + delimiter.length());
	       		cols++;
	   		}
	   		cols=0;
	   		rows++;
       	}
	} else {
		cout << "Unable to open file f_in"; 
		return 1;
	}	
	f_in.close();

	/* Parse Training Output */
	path = pathOut;
	path.append(filename);
	path.append(extension);
	//cout << path << endl;

	rows=0,cols=0;
    /* OUTPUT TRAINING MATRIX */
	ifstream f_res (path);
	if (f_res.is_open()){
		while (getline(f_res,line)){
			// trim leading spaces
			line.erase(line.find_last_not_of(" \n\r\t")+1);
			trainOutMatrix.resize(rows+1);
			pos = line.find(delimiter);
			if(pos<0){
				// in case train matrix is a single column
				pos=1;
			}
			while(line.length()){
				trainOutMatrix.at(rows).resize(cols+1);
	       		string token = line.substr(0, pos);
	       		double x = stoi(token, 0, 16);
	       		trainOutMatrix.at(rows).at(cols) = x;
	       		line.erase(0, pos + delimiter.length());
	       		cols++;
	   		}
	   		cols=0;
	   		rows++;
       	}
	} else {
		cout << "Unable to open file f_res"; 
		return 1;
	}	
	f_res.close();

	return 0;
}

void Net::printTrainMatrix(){
	cout << "trainInMatrix"<< endl;
	for (unsigned i = 0; i < trainInMatrix.size(); ++i)
	{
		for (unsigned j = 0; j < trainInMatrix.at(i).size(); ++j)
		{
			cout << trainInMatrix.at(i).at(j) << " ";	
		}
		cout << endl;
	}

	cout << "trainOutMatrix"<< endl;
	for (unsigned i = 0; i < trainOutMatrix.size(); ++i)
	{
		for (unsigned j = 0; j < trainOutMatrix.at(i).size(); ++j)
		{
			cout << trainOutMatrix.at(i).at(j) << " ";	
		}
		cout << endl;
	}
}

void Net::plotGraph(){
   	plt::plot(this->graphXval,this->graphErr);
   	plt::show();
	return;
}