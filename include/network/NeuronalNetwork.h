/*
 * NeuroanlNetwork.h
 *
 *  Created on: Nov 30, 2015
 *      Author: Nelson Victor Cruz Hdez
 */

#ifndef NEUROANLNETWORK_H_
#define NEUROANLNETWORK_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class NeuronalNetwork{
	public:
		int totalInputs;
		int hiddenLayerSize;
		int minEpochsApplied;
		double learningRate;
		vector< vector<double>  >  inputHiddenWeightsVector;
		vector<double> hiddenOutputWeightsVector;
		vector<double> hiddenLayerValuesVector;

		//Constructor
		NeuronalNetwork(int totalInputs, int hiddenLayerSize, int minEpochsApplied, double learningRate);

		//Neurons functions
		double sigmoidFunction(double x);
		double sigmoidDerivate(double x);

		//Neuronal network
		void initWeights();
		double neuronalNetworkExecution(vector<int> currentInput);
		void backPropagation(vector<int> currentInput, double output, double error);
		void training(vector < vector<int> > trainingMatrix, vector<int> results);

		//Utilities
		double randomNumber();
		double randomWeight();
		void printNeuronalNetwork();
};

#endif /* NEUROANLNETWORK_H_ */
