#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <network/NeuronalNetwork.h>

class Interface : public Gtk::Window{
  public:
    Interface();
    virtual ~Interface();

    //Buffers
  	Glib::RefPtr<Gtk::TextBuffer> noteSelectedBuffer;
  	Glib::RefPtr<Gtk::TextBuffer> stringSelectedBuffer;
  	Glib::RefPtr<Gtk::TextBuffer> instrumentSelectedBuffer;
    Glib::RefPtr<Gtk::TextBuffer> samplesCounterBuffer;
    Glib::RefPtr<Gtk::TextBuffer> hitsBuffer;
    Glib::RefPtr<Gtk::TextBuffer> epochsBuffer;
    Glib::RefPtr<Gtk::TextBuffer> errorBuffer;
  		
  	//Scrollbar
  	Glib::RefPtr<Gtk::Adjustment> m_adjustment;
  	Gtk::Scale m_VScale;

    //Functionality
    int inputs;
    int hiddenLayerSize;
    int minEpochsApplied;
    double learningRate;
    int nnTrained;

    NeuronalNetwork *neuronalNetwork;
    //No se va a inicializar hasta que se mande a llamar
    vector < vector <int> > trainingMatrix;
    vector < vector <int> > realMatrix;
    //No se va a inicializar hasta que se mande a llamar
    vector<int> results;

    vector < vector <int> > container;

    void initNeuronalNetworkFunctionality();

	private:
  	// Signal handlers:
  	void quitBtnPressed();
  	void startRecordingBtnPressed(const Glib::ustring& data);
  	void changeNote();
  	void changeString();
  	void changeInstrument();
  	void changeScrollbar();
    void classChanged();

    void cleanSamples();
    void recordSample();
    void createTestTM();
    void createTestReal();
    void printTrainingMatrix();
    void printClasses();
    void trainNeuronalNetwork();
    void evaluateForRealSamples();

  	// Child widgets:
  		
  	// Grids
  	Gtk::Grid interfaceGrid;
    Gtk::Grid leftGrid;
    Gtk::Grid rightGrid;

    //Combo
    Gtk::ComboBoxText classCombo;

  	// Buttons
  	Gtk::Button startRecordingBtn, indentifyInstrumentBtn, loadNetworkBtn, changeNoteBtn, changeStringBtn, changeTunerBtn, changeInstumentBtn, quitBtn,
                  recordSampleBtn, cleanTrainingBtn, startTrainingBtn;
};

#endif /* GTKMM_EXAMPLEWINDOW_H */
