#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

class Interface : public Gtk::Window{
	public:
		Interface();
		virtual ~Interface();

		//Buffers
  		Glib::RefPtr<Gtk::TextBuffer> noteSelectedBuffer;
  		Glib::RefPtr<Gtk::TextBuffer> stringSelectedBuffer;
  		Glib::RefPtr<Gtk::TextBuffer> instrumentSelectedBuffer;
  		
  		//Scrollbar
  		Glib::RefPtr<Gtk::Adjustment> m_adjustment;
  		Gtk::Scale m_VScale;

	private:
  		// Signal handlers:
  		void quitBtnPressed();
  		void startRecordingBtnPressed(const Glib::ustring& data);
  		void changeNote();
  		void changeString();
  		void changeInstrument();
  		void changeScrollbar();

  		// Child widgets:
  		
  		// Grids
  		Gtk::Grid interfaceGrid;

  		// Buttons
  		Gtk::Button startRecordingBtn, changeNoteBtn, changeStringBtn, changeTunerBtn, changeInstumentBtn, quitBtn;
};

#endif /* GTKMM_EXAMPLEWINDOW_H */