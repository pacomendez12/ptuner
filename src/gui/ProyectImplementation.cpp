#include <iostream>
#include <gui/ProyectImplementation.h>

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
  startTrainingBtn("Start Training"){

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

  Gtk::TextView *noteSelectedTxtView = new Gtk::TextView;
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
  startRecordingBtn.signal_clicked().connect(sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &Interface::startRecordingBtnPressed), "Start recording") );
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
  
  initNeuronalNetworkFunctionality();
  createTestTM();
  createTestReal();

  show_all_children();
}

Interface::~Interface(){}

void Interface::quitBtnPressed(){
  hide();
}

void
Interface::startRecordingBtnPressed(const Glib::ustring& data){
  std::cout << data << " was pressed" << std::endl;
}

void Interface::changeNote(){
  std::vector<int> something = {1,2,3,4,5};
  int random = rand()%(4) + 1;
  noteSelectedBuffer->set_text("" + something[random]);
}

void Interface::changeString(){
  /*
  std::vector<int> something = {11,12,13,14,15};
  int random = rand()%(4) + 1;
  stringSelectedBuffer->set_text("" + something[random]);
  */
  neuronalNetwork->printNeuronalNetwork();
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
  this->inputs = 25;
  this->hiddenLayerSize = 13;
  this->minEpochsApplied = 1000;
  this->learningRate = 1.0;
  this->neuronalNetwork = new NeuronalNetwork(inputs,hiddenLayerSize, minEpochsApplied, learningRate);
}

void Interface::cleanSamples(){
  trainingMatrix.clear();
  results.clear();
  samplesCounterBuffer->set_text ("0/12");
  errorBuffer->set_text ("Ya no hay muestras para entrenar la red.");
}

void Interface::recordSample(){
  int trainingMatrixSize = trainingMatrix.size();
  if(trainingMatrixSize == 12){
    errorBuffer->set_text ("El limite de muestras se ha alcanzado");
    return;
  }

  //Declaracion de las clases
  Glib::ustring text = classCombo.get_active_text();
  
  if(text.compare("Guitarra") == 0){
    results.push_back(0);
  }

  if(text.compare("Chelo") == 0){
    results.push_back(1);
  }

  //TODO:Aqui es donde vamos a mandar a llamar la parte de grabar
  vector<int> currentVector = container[trainingMatrixSize];
  trainingMatrix.push_back(currentVector);
  //TODO: Colocar correctamente cuatos d ecuantos llevamos
  samplesCounterBuffer->set_text ("Hubo un aumento");
  errorBuffer->set_text ("");
}

//For test purposes
void Interface::createTestTM(){
  vector<int> v = {0,1,1,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,1,1,0};
  vector<int> v2 = {1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1};
  vector<int> v3 = {0,1,1,1,0,0,1,1,1,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0};
  vector<int> v4 = {1,0,0,0,1,0,1,1,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1};
  vector<int> v5 = {0,0,1,0,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0};
  vector<int> v6 = {1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,1,1,0,1,0,0,0,1};
  vector<int> v7 = {1,0,0,0,1,0,1,0,1,0,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1};
  vector<int> v8 = {1,0,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,0,1,0,1,0,0,0,1};
  vector<int> v9 = {0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0};
  vector<int> v10 = {1,1,0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,0,1,1};
  vector<int> v11 = {0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0};
  vector<int> v12 = {0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0};

  container.push_back(v);
  container.push_back(v2);
  container.push_back(v3);
  container.push_back(v4);
  container.push_back(v5);
  container.push_back(v6);
  container.push_back(v7);
  container.push_back(v8);
  container.push_back(v9);
  container.push_back(v10);
  container.push_back(v11);
  container.push_back(v12);
}

void Interface::createTestReal(){
  vector<int> rv = {0,1,1,1,0,0,1,0,1,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0};
  vector<int> rv2 = {0,1,1,1,0,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,0,1,1,1,0};
  vector<int> rv3 = {1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1};
  vector<int> rv4 = {1,0,0,0,1,1,1,0,1,1,0,1,1,1,0,0,1,1,1,0,1,1,0,1,1};

  realMatrix.push_back(rv);
  realMatrix.push_back(rv2);
  realMatrix.push_back(rv3);
  realMatrix.push_back(rv4);
}

void Interface::printTrainingMatrix(){
  int tmSize = trainingMatrix.size();
  for(int i=0; i<tmSize; i++){
    vector<int> v = trainingMatrix[i];
    int localVectorSize = v.size();
    for(int y=0; y<localVectorSize; y++){
      printf("%d,",v[y]);
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
  printf("Inicializando entrenamiento desde interfaz\n");
  int trainingMatrixSize = trainingMatrix.size();
  if(trainingMatrixSize < 12){
    errorBuffer->set_text ("Se necesitan al menos 12 muestras para entrenar la red");
    return;
  }


  printTrainingMatrix();
  printClasses();

  neuronalNetwork->training(trainingMatrix,results);
  nnTrained = 1;
  printf("Resultados del entrenamiento\n"
      "HITS: %d\n"
      "EPOCHS: %d\n", neuronalNetwork->hits, neuronalNetwork->epochs);
  errorBuffer->set_text ("La red neuronal ha terminado de entrenarse");
  //TODO: Cambiar los mensajes
  hitsBuffer->set_text ("Hits:");
  epochsBuffer->set_text ("Epochs:");
}

void Interface::evaluateForRealSamples(){
  if(nnTrained == 0){
    errorBuffer->set_text ("La red neuronal no ha sido entrenada, entrenarla o cargar configuracion");
    return;
  }
  
  printf("Resultados obtenidos con una red entrenada previamente\n");
  for(int i=0; i<4; i++){
    printf("%f\n",neuronalNetwork->neuronalNetworkExecution(realMatrix[i]));
  }
}