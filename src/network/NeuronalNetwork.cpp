#include <network/NeuronalNetwork.h>

using namespace std;

//Constructor
NeuronalNetwork::NeuronalNetwork(int totalInputs,int hiddenLayerSize, int minEpochsApplied, double learningRate){
	this->totalInputs = totalInputs;
	this->hiddenLayerSize = hiddenLayerSize;
	this->minEpochsApplied = minEpochsApplied;
	this->learningRate = learningRate;

	//Initialize Neuronal Network;
	initWeights();
}

//Neurons functions
double NeuronalNetwork::sigmoidFunction(double x){
	return 1.0/(1 + exp(-x));
}

double NeuronalNetwork::sigmoidDerivate(double x){
	return x * (1 - x);
}

//Neuronal network
void NeuronalNetwork::initWeights(){
	//Initialize neuronal network

	//Init input to hidden layer weights vector
	for(int i=0; i<totalInputs; i++){
		inputHiddenWeightsVector.push_back(vector <double>());
	}

	//Init input to hidden layer weights values
	for(int i=0; i<totalInputs; i++){
		for(int y=0; y<hiddenLayerSize; y++){
			inputHiddenWeightsVector[i].push_back(randomNumber());
		}
	}

	//Init hidden to output layer weights values
	for(int z=0; z<hiddenLayerSize; z++){
		hiddenOutputWeightsVector.push_back(randomNumber());
	}
}

double NeuronalNetwork::neuronalNetworkExecution(vector<int> currentInput){
	double output = 0;
	int currentInputSize = currentInput.size();

	//printf("currentInputSize: %d\n", currentInputSize);
	/*
	* It goes from 0 to the total neurons in the hidden layer
	* When this for finishes, al the hidden layer neurons,could be activated or not
	* in order to pass this new value to next layer and this values is allocated in hiddenLayerValuesVector
	* where h is every neuron
	*/
	//printf("Layer input hidden\n");
	for(int h=0; h<hiddenLayerSize; h++){
		double sums = 0;
		for(int i=0; i<currentInputSize; i++){
			//printf("current: %d,%d:%d\n",h,i,currentInput[i]);
			sums += currentInput[i] * inputHiddenWeightsVector[i][h];
		}
		//printf("Termino suma\n");
		hiddenLayerValuesVector.push_back(sigmoidFunction(sums));
	}

	/*
	* Activation function for the last neuron in the perceptron
	* Result values from the hidden layer to the last neuron
	*/
	//printf("Layer hidden output\n");
	for(int h=0; h<hiddenLayerSize; h++){
		output += hiddenLayerValuesVector[h] * hiddenOutputWeightsVector[h];
	}

	output = sigmoidFunction(output);

	return output;
}

void NeuronalNetwork::backPropagation(vector<int> currentInput, double output, double error){
	//Output delta for hidden layer
	double outputDelta = error * sigmoidDerivate(output);
	int inputSize = currentInput.size();

	//Adjust of weights of the hidden layer
	for(int h=0; h<hiddenLayerSize; h++){
		hiddenOutputWeightsVector[h] += hiddenLayerValuesVector[h] * learningRate * outputDelta;
	}

	//Output delta for input layer
	vector<double> hiddenDeltas;
	for(int h=0; h<hiddenLayerSize; h++){
		double currentDelta = sigmoidDerivate(hiddenLayerValuesVector[h]) * outputDelta * hiddenOutputWeightsVector[h];
		hiddenDeltas.push_back(currentDelta); 
	}

	for(int i=0; i<inputSize; i++){
		for(int h=0; h<hiddenLayerSize; h++){
			inputHiddenWeightsVector[i][h] += currentInput[i] * learningRate * hiddenDeltas[h];
		}
	}
}

void NeuronalNetwork::training(vector < vector<int> > trainingMatrix, vector<int> results){
	//Has all the elements that we will test to train the matrix
	int epochSize = results.size();
	
	printf("In training, %d\n",epochSize);
	
	int hits=0;
	int currentRow = 0;
	int epochs = 0;

	while(epochSize > hits && epochs < minEpochsApplied){
	//while(currentRow < epochSize){
		vector<int> currentInput = trainingMatrix[currentRow];

		//Result of evaluating completly one element of the set
		double output = neuronalNetworkExecution(currentInput);

		
		//Adjust values
		double expectedValue = results[currentRow] == 0 ? 0.25 : 0.75;
		double error = expectedValue - output;

		/*
		* 0.25 is the range, the abs is used to check if the value is in the correct range
		*/
		if(abs(error) <= 0.25){
			hits++;
		}else{
			//printf("Previous hits: %d\n",hits);
			hits = 0;
			backPropagation(currentInput, expectedValue, error);
		}
		

		currentRow++;
		
		if(currentRow == epochSize){
			epochs++;
			currentRow = 0;
		}		
	}
	printf("HITS: %d\nEPOCHS: %d\nFINISH TRAINING\n", hits, epochs);
}

//Utilities
double NeuronalNetwork::randomNumber(){
    return -0.1 + 0.2 * rand();
}

void NeuronalNetwork::printNeuronalNetwork(){
	printf("Weights from input to hidden vector\n");
	for(int i=0; i<totalInputs; i++){
		for(int y=0; y<hiddenLayerSize; y++){
			printf("%d,%d,%f\n",i,y,inputHiddenWeightsVector[i][y]);
		}
	}

	
	printf("Weights from hidden to output\n");
	for(int z=0; z<hiddenLayerSize; z++){
		printf("%f\n",hiddenOutputWeightsVector[z]);
	}
}