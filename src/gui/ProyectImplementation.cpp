#include <iostream>
#include <gui/ProyectImplementation.h>
#include <tuner/tuner.h>

using namespace std;

Interface::Interface() 
: 
  startRecordingBtn("Start Recording"),
  changeNoteBtn("Change Note"), 
  changeStringBtn("Change String"), 
  changeTunerBtn("Change Tuner"), 
  changeInstumentBtn("Change Instrument"),
  indentifyInstrumentBtn("Indentify Instrument"),
  loadNetworkBtn("Load Trained Neuronal Network"), 
  quitBtn("Quit application"), 
  m_adjustment( Gtk::Adjustment::create(0.0, -50.0, 50.0, 1.0, 1.0) ),
  m_VScale(m_adjustment, Gtk::ORIENTATION_HORIZONTAL),
  recordSampleBtn("Record sample"),
  cleanTrainingBtn("Clean samples"),
  startTrainingBtn("Start Training"),
  textMutex()
{
  tuner = new Tuner();
  this->nnTrained = 0;

  set_title("Identifying sounds and instruments");
  set_border_width(5);

  //Combo
  classCombo.append("Guitarra");
  classCombo.append("Chelo");
  classCombo.append("Violin");
  classCombo.set_active(1);

  // Text Views
  Gtk::TextView *noteTxtView = new Gtk::TextView;
  Glib::RefPtr<Gtk::TextBuffer> noteBuffer = noteTxtView->get_buffer();
  noteBuffer->set_text ("Note: ");

  //Gtk::TextView *noteSelectedTxtView = new Gtk::TextView;
  noteSelectedTxtView = new Gtk::TextView;
  noteSelectedBuffer = noteSelectedTxtView ->get_buffer();
  noteSelectedBuffer->set_text ("Do");

  Gtk::TextView *stringTxtView = new Gtk::TextView;
  Glib::RefPtr<Gtk::TextBuffer> stringBuffer = stringTxtView->get_buffer();
  stringBuffer->set_text ("String: ");

  Gtk::TextView *selectedStringTxtView = new Gtk::TextView;
  stringSelectedBuffer = selectedStringTxtView ->get_buffer();
  stringSelectedBuffer->set_text ("5");

  Gtk::TextView *instrumentTxtView = new Gtk::TextView;
  Glib::RefPtr<Gtk::TextBuffer> instrumentBuffer = instrumentTxtView->get_buffer();
  instrumentBuffer->set_text ("Instrument: ");

  Gtk::TextView *instrumentSelectedTxtView = new Gtk::TextView;
  instrumentSelectedBuffer = instrumentSelectedTxtView->get_buffer();
  instrumentSelectedBuffer->set_text ("Guitarra");

  Gtk::TextView *selectClassTxtView = new Gtk::TextView;
  Glib::RefPtr<Gtk::TextBuffer> selectClassBuffer = selectClassTxtView->get_buffer();
  selectClassBuffer->set_text ("Select class:");

  Gtk::TextView *samplesCounterTxtView = new Gtk::TextView;
  samplesCounterBuffer = samplesCounterTxtView ->get_buffer();
  samplesCounterBuffer->set_text ("0/12");

  Gtk::TextView *hitsTxtView = new Gtk::TextView;
  hitsBuffer = hitsTxtView->get_buffer();
  hitsBuffer->set_text ("No hits yet");

  Gtk::TextView *epochsTxtView = new Gtk::TextView;
  epochsBuffer = epochsTxtView->get_buffer();
  epochsBuffer->set_text ("No epochs yet");

  Gtk::TextView *errorTxtView = new Gtk::TextView;
  errorBuffer = errorTxtView->get_buffer();
  errorBuffer->set_text ("");

  //Interface construction
  add(interfaceGrid);
  interfaceGrid.attach(leftGrid,0,0,3,7);
  interfaceGrid.attach(rightGrid,4,0,3,7);

  // Tuner
  //First row
  leftGrid.attach(startRecordingBtn,0,0,1,1);
  leftGrid.attach(*noteTxtView,1,0,1,1);
  leftGrid.attach(*noteSelectedTxtView,2,0,1,1);
  //Second row
  leftGrid.attach(*stringTxtView,1,2,1,1);
  leftGrid.attach(*selectedStringTxtView,2,2,1,1);
  //Third row
  leftGrid.attach(m_VScale,0,3,3,1);
  //Fourth row
  leftGrid.attach(indentifyInstrumentBtn,0,4,1,1);
  leftGrid.attach(loadNetworkBtn,3,4,1,1);
  //Fivth row
  leftGrid.attach(*instrumentTxtView,0,5,1,1);
  leftGrid.attach(*instrumentSelectedTxtView,3,5,1,1);
  //Last row
  leftGrid.attach(quitBtn,0,6,3,1);

  //Optional
  leftGrid.attach(changeNoteBtn,0,7,1,1);
  leftGrid.attach(changeStringBtn,0,8,1,1);
  leftGrid.attach(changeTunerBtn,0,9,1,1);
  leftGrid.attach(changeInstumentBtn,0,10,1,1);

  // Neuronal Network
  //First Row
  rightGrid.attach(*selectClassTxtView,0,0,1,1);
  rightGrid.attach(classCombo,3,0,1,1);
  //Second row
  rightGrid.attach(recordSampleBtn,0,1,1,1);
  rightGrid.attach(*samplesCounterTxtView,3,1,1,1);
  //Third row
  rightGrid.attach(cleanTrainingBtn,1,3,1,1);
  //Fourth row
  rightGrid.attach(startTrainingBtn,1,4,1,1);
  //Fivth row
  rightGrid.attach(*hitsTxtView,1,5,1,1);
  //Siwxth row
  rightGrid.attach(*epochsTxtView,1,6,1,1);
  //Seventh row
  rightGrid.attach(*errorTxtView,1,7,1,1);
  
  //Events
  startRecordingBtn.signal_clicked().connect(sigc::mem_fun(*this, &Interface::startRecordingBtnPressed));
  changeNoteBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::changeNote));
  changeStringBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::changeString));
  changeTunerBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::changeScrollbar));
  changeInstumentBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::changeInstrument));
  quitBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::quitBtnPressed));
  cleanTrainingBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::cleanSamples));
  recordSampleBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::recordSample));
  classCombo.signal_changed().connect(sigc::mem_fun(*this,&Interface::classChanged) );
  startTrainingBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::trainNeuronalNetwork) );
  indentifyInstrumentBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::evaluateForRealSamples) );
  loadNetworkBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::importTrainedNeuronalNetwork) );

  initNeuronalNetworkFunctionality();
  //createTestTM();
  //createTestReal();

  tuner->gui = this;
  show_all_children();
}

Interface::~Interface(){
	if (tuner != NULL) {
		delete tuner;
	}
}

void Interface::quitBtnPressed(){
  hide();
}

void
Interface::startRecordingBtnPressed(){
  printf("Start recording pressed\n");
  tuner->startTuning();
}

void Interface::changeNote(){
  std::vector<int> something = {1,2,3,4,5};
  int random = rand()%(4) + 1;
  noteSelectedBuffer->set_text("" + something[random]);
}

void Interface::changeString(){
  
  std::vector<int> something = {11,12,13,14,15};
  int random = rand()%(4) + 1;
  stringSelectedBuffer->set_text("" + something[random]);
  
  //neuronalNetwork->printNeuronalNetwork();
}

void Interface::changeInstrument(){
  std::vector<int> something = {11,12,13,14,15};
  int random = rand()%(4) + 1;
  instrumentSelectedBuffer->set_text("" + something[random]);
}

void Interface::changeScrollbar(){
  std::vector<int> something = {11,12,13,14,15};
  int random = rand()%(100) + 1;
  m_adjustment->set_value(random);
}

void Interface::classChanged(){
  Glib::ustring text = classCombo.get_active_text();
  if(!(text.empty()))
    std::cout << "Combo changed: " << text << std::endl;
}

void Interface::initNeuronalNetworkFunctionality(){
  this->inputs = TOTAL_INPUTS;
  this->hiddenLayerSize = HIDDEN_LAYER_SIZE;
  this->minEpochsApplied = MIN_EPOCHS_APPLY;
  this->learningRate = LEARNING_RATE;
  this->neuronalNetwork = new NeuronalNetwork(inputs,hiddenLayerSize, minEpochsApplied, learningRate);
}

void Interface::cleanSamples(){
  trainingMatrix.clear();
  results.clear();
  samplesCounterBuffer->set_text ("0/12");
  errorBuffer->set_text ("Ya no hay muestras para entrenar la red.");
}

void Interface::recordSample(){
  int guitarSize = guitarVector.size();
  int violinSize = violinVector.size();
  int bassSize = bassVector.size();

  int totalAmount = guitarSize + violinSize + bassSize;
  
  if(totalAmount == TRAINING_MATRIX_SIZE){
    errorBuffer->set_text ("El limite de muestras se ha alcanzado");
    return;
  }

  //Start recording
  tuner->startTuning();
  double * arr = tuner->getProcessedArray();
  //vector<double> currentVector;
  /*for(int i=0; i<TOTAL_INPUTS; i++){
    printf("%f,",arr[i]);
    currentVector.push_back(arr[i]);
  }
  printf("eeeeee\n");
  for(int i=0; i<TOTAL_INPUTS; i++){
    printf("%f,",currentVector[i]);
    //currentVector.push_back(arr[i]);
  }*/
  vector<double> currentVector(arr, arr + TOTAL_INPUTS);
  int vSize = currentVector.size();
  printf("vector v size: %d\n",vSize);

  //TODO: check if it working
  tuner->stopTuning();


  //Declaracion de las clases
  Glib::ustring text = classCombo.get_active_text();
  
  if(text.compare("Guitarra") == 0){
    guitarVector.push_back(currentVector);
  }

  if(text.compare("Violin") == 0){
    violinVector.push_back(currentVector);
  }

  //TODO: Agregar la otra clase que vamos a empezar a analizar
  
  //TODO: Colocar correctamente cuaNtos de cuantos llevamos
  samplesCounterBuffer->set_text ("Hubo un aumento");
  errorBuffer->set_text ("");

  guitarSize = guitarVector.size();
  violinSize = violinVector.size();
  bassSize = bassVector.size();

  totalAmount = guitarSize + violinSize + bassSize;

  printf("El total de muestras obtenidas es: %d\n", totalAmount);
}

void Interface::printTrainingMatrix(){
  int tmSize = trainingMatrix.size();
  for(int i=0; i<tmSize; i++){
    vector<double> v = trainingMatrix[i];
    int localVectorSize = v.size();
    for(int y=0; y<localVectorSize; y++){
      printf("%f,",v[y]);
    }
    printf("\n");
  }
}

void Interface::printClasses(){
  printf("Clases\n");
  int resultsSize = results.size();
  for(int i=0; i<resultsSize; i++){
      printf("%d,",results[i]);
  }
}

void Interface::trainNeuronalNetwork(){
  printf("Inicializando entrenamiento\n");

  int guitarSize = guitarVector.size();
  int violinSize = violinVector.size();
  int bassSize = bassVector.size();

  int totalAmount = guitarSize + violinSize + bassSize;
  
  if(totalAmount < TRAINING_MATRIX_SIZE){
    errorBuffer->set_text ("Se necesitan al menos 24 muestras para entrenar la red");
    return;
  }

  printf("Se va a borrar el entrenamiento previo de la red neuronal\n");
  
  if(std::remove("nn-weights.data")!= 0){
    printf("Error al borrar el archivo nn-weights.data");
  }else{
    printf("El archivo fue eliminado correctamente");
  }

  //TODO: Hacer la mezcla de las muestras y las clases
  for(int i=0; i<12; i++){
    vector<double> guitar = guitarVector[i];
    vector<double> violin = violinVector[i];
    trainingMatrix.push_back(guitar);
    trainingMatrix.push_back(violin);
    results.push_back(0);
    results.push_back(1);
  }

  //printTrainingMatrix();
  //printClasses();

  neuronalNetwork->training(trainingMatrix,results);
  
  nnTrained = 1;
  
  printf("Resultados del entrenamiento\n"
      "HITS: %d\n"
      "EPOCHS: %d\n", neuronalNetwork->hits, neuronalNetwork->epochs);
  errorBuffer->set_text ("La red neuronal ha terminado de entrenarse");
  
  //TODO: Cambiar los mensajes
  hitsBuffer->set_text ("Hits:");
  epochsBuffer->set_text ("Epochs:");

  exportTrainedNeuronalNetwork();
}

void Interface::evaluateForRealSamples(){
  if(nnTrained == 0){
    errorBuffer->set_text ("La red neuronal no ha sido entrenada, entrenarla o cargar configuracion");
    return;
  }
  
  printf("Resultados obtenidos con una red entrenada previamente\n");


  printf("Grabando...\n");
  tuner->startTuning();
  double * arr = tuner->getProcessedArray();
  vector<double> currentVector(arr, arr + 256);
  int vSize = currentVector.size();
  printf("vector v size: %d\n",vSize);
  printf("Termino de grabar\n");


  printf("Entra a procesamiento\n");
  double result = neuronalNetwork->neuronalNetworkExecution(currentVector);
  if(result <= 5.0){
    printf("Es una guitarra");
  }else if(result > 5.0){
    printf("Es un violin");
  }
}

void Interface::exportTrainedNeuronalNetwork(){
  //Initialize file
  int totalInputs = neuronalNetwork->totalInputs;
  int hiddenLayerSize = neuronalNetwork->hiddenLayerSize;
  ofstream fs;
  fs.open("network-data.dat");

  //Export input to hidden weights
  for(int i=0; i<totalInputs; i++){
    for(int h=0; h<hiddenLayerSize;h++){
      double currentWeight = neuronalNetwork->inputHiddenWeightsVector[i][h];
      fs << std::fixed << std::setprecision(8) << currentWeight;
      fs << "\n";
    }
  }

  for(int y=0; y<hiddenLayerSize; y++){
    double currentWeight = neuronalNetwork->hiddenOutputWeightsVector[y];
    fs << std::fixed << std::setprecision(8) << currentWeight;
    fs << "\n";
  }

  fs.close();
  printf("Se termino de guardar el entrenamiento en nn-weights.data\n");
}

void Interface::importTrainedNeuronalNetwork(){
  //Initialize file
  int totalInputs = neuronalNetwork->totalInputs;
  int hiddenLayerSize = neuronalNetwork->hiddenLayerSize;
  int totalWeights = (totalInputs * neuronalNetwork->hiddenLayerSize) + (hiddenLayerSize);
  vector<double> weights;
  nnTrained = 1;

  ifstream infile; 
  infile.open("network-data.dat"); 

  double currentWeight = 0.0;

  //Export input to hidden weights
  for(int i=0; i<totalInputs; i++){
    for(int h=0; h<hiddenLayerSize;h++){
      infile >> currentWeight; 
      neuronalNetwork->inputHiddenWeightsVector[i][h] = currentWeight;
    }
  }

  for(int y=0; y<hiddenLayerSize; y++){
    infile >> currentWeight;
    neuronalNetwork->hiddenOutputWeightsVector[y] = currentWeight;
  }

  infile.close();
  
  printf("Se termino de exportar los datos\n");
}

