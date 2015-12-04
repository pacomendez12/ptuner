#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>

class UIClassifer : public Gtk::Window{
	public:
  		UIClassifer();
  		virtual ~UIClassifer();

	protected:
  		// Signal handlers:
  		// Our new improved on_button_clicked(). (see below)
  		void on_button_clicked(Glib::ustring data);

  		// Child widgets:

  		//Labels
  		Gtk::Label nota_lbl, cuerda_lbl;

  		//Separators
  		Gtk::Separator separator1, separator2;

  		//Boxes
  		Gtk::Box start_box;
  		Gtk::Box which_note_row_box;
  		Gtk::Box graph_box;
  		Gtk::Box instrument_box;

  		//Buttons
  		Gtk::Button start_btn;
};

#endif // GTKMM_EXAMPLE_HELLOWORLD_H