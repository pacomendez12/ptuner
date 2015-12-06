#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include <network/NeuronalNetwork.h>
#include <tuner/tuner.h>

#define TRAINING_MATRIX_SIZE 24
#define HIDDEN_LAYER_SIZE 128
#define TOTAL_INPUTS 256
#define MIN_EPOCHS_APPLY 1000
#define LEARNING_RATE 1.0

class Interface : public Gtk::Window{
  public:
    Interface();
    virtual ~Interface();

    //GUI
    
    //Buffers
  	Glib::RefPtr<Gtk::TextBuffer> noteSelectedBuffer;
  	Glib::RefPtr<Gtk::TextBuffer> stringSelectedBuffer;
  	Glib::RefPtr<Gtk::TextBuffer> instrumentSelectedBuffer;
    Glib::RefPtr<Gtk::TextBuffer> samplesCounterBuffer;
    Glib::RefPtr<Gtk::TextBuffer> hitsBuffer;
    Glib::RefPtr<Gtk::TextBuffer> epochsBuffer;
    Glib::RefPtr<Gtk::TextBuffer> errorBuffer;
  	
    // Child widgets:
    
    //Scrollbar
  	Glib::RefPtr<Gtk::Adjustment> m_adjustment;
  	Gtk::Scale m_VScale;
  
    //Grids
    Gtk::Grid interfaceGrid;
    Gtk::Grid leftGrid;
    Gtk::Grid rightGrid;

    //Combo
    Gtk::ComboBoxText classCombo;

    // Buttons
    Gtk::Button startRecordingBtn, indentifyInstrumentBtn, loadNetworkBtn, changeNoteBtn, changeStringBtn, changeTunerBtn, changeInstumentBtn, quitBtn,
                  recordSampleBtn, cleanTrainingBtn, startTrainingBtn;

    //Functionality
    int inputs;
    int hiddenLayerSize;
    int minEpochsApplied;
    double learningRate;
    int nnTrained;

    NeuronalNetwork *neuronalNetwork;
    Tuner tuner;
    vector < vector <double> > trainingMatrix;
    vector < vector <double> > guitarVector;
    vector < vector <double> > violinVector;
    vector < vector <double> > bassVector;
    vector < vector <double> > realMatrix;
    vector<int> results;
    vector<int> resultsGuitar;
    vector<int> resultsViolin;
    vector<int> resultsBass;
    vector < vector <int> > container;

	private:
  	// Signal handlers methods
  	void quitBtnPressed();
  	void startRecordingBtnPressed();
  	void changeNote();
  	void changeString();
  	void changeInstrument();
  	void changeScrollbar();
    void classChanged();
    void cleanSamples();
    void recordSample();
    //void createTestTM();
    //void createTestReal();
    void printTrainingMatrix();
    void printClasses();
    void trainNeuronalNetwork();
    void evaluateForRealSamples();
    void importTrainedNeuronalNetwork();
    void initNeuronalNetworkFunctionality();
    void exportTrainedNeuronalNetwork();
};

#endif /* GTKMM_EXAMPLEWINDOW_H */
