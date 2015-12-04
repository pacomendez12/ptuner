#include <iostream>
#include "Interface.h"

Interface::Interface() 
: 
  startRecordingBtn("Start Recording"),
  changeNoteBtn("Change Note"), 
  changeStringBtn("Change String"), 
  changeTunerBtn("Change Tuner"), 
  changeInstumentBtn("Change Instrument"), 
  quitBtn("Quit application"), 
  m_adjustment( Gtk::Adjustment::create(0.0, -50.0, 50.0, 1.0, 1.0) ),
  m_VScale(m_adjustment, Gtk::ORIENTATION_HORIZONTAL){

  set_title("Identifying sounds and instruments");
  set_border_width(5);

 

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

  //Interface construction
  add(interfaceGrid);

  interfaceGrid.attach(startRecordingBtn,0,0,1,1);
  interfaceGrid.attach(*noteTxtView,1,0,1,1);
  interfaceGrid.attach(*noteSelectedTxtView,2,0,1,1);
  interfaceGrid.attach(*stringTxtView,1,2,1,1);
  interfaceGrid.attach(*selectedStringTxtView,2,2,1,1);
  interfaceGrid.attach(m_VScale,0,3,3,4);
  interfaceGrid.attach(*instrumentTxtView,0,8,1,1);
  interfaceGrid.attach(*instrumentSelectedTxtView,1,8,2,1);
  interfaceGrid.attach(quitBtn,0,9,3,1);
  interfaceGrid.attach(changeNoteBtn,0,10,3,1);
  interfaceGrid.attach(changeStringBtn,0,11,3,1);
  interfaceGrid.attach(changeTunerBtn,0,12,3,1);
  interfaceGrid.attach(changeInstumentBtn,0,13,3,1);

  
  //Events
  startRecordingBtn.signal_clicked().connect(sigc::bind<Glib::ustring>( sigc::mem_fun(*this, &Interface::startRecordingBtnPressed), "Start recording") );
  changeNoteBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::changeNote));
  changeStringBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::changeString));
  changeTunerBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::changeScrollbar));
  changeInstumentBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::changeInstrument));
  quitBtn.signal_clicked().connect(sigc::mem_fun(*this,&Interface::quitBtnPressed));
  
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
  std::vector<int> something = {11,12,13,14,15};
  int random = rand()%(4) + 1;
  stringSelectedBuffer->set_text("" + something[random]);
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