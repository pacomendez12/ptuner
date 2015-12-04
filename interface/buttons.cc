#include "buttons.h"
#include <iostream>

UIClassifer::UIClassifer(): start_btn("Start functionality"){
  // This just sets the title of our new window.
  set_title("Classifer!");

  // sets the border width of the window.
  set_border_width(10);

  // put the boxes into the main window.
  add(start_box);
  add(which_note_row_box);
  add(graph_box);
  add(instrument_box);

  start_btn.signal_clicked().connect(
  								sigc::bind<Glib::ustring>(
  									sigc::mem_fun(*this, &UIClassifer::on_button_clicked), "Button start pressed"));

  // instead of gtk_container_add, we pack this button into the invisible
  // box, which has been packed into the window.
  // note that the pack_start default arguments are Gtk::EXPAND | Gtk::FILL, 0
  start_box.pack_start(start_btn);

  // always remember this step, this tells GTK that our preparation
  // for this button is complete, and it can be displayed now.
  start_btn.show();

  start_box.show();
}

UIClassifer::~UIClassifer(){}

// Our new improved signal handler.  The data passed to this method is
// printed to stdout.
void UIClassifer::on_button_clicked(Glib::ustring data){
  std::cout << "Hello World - " << data << " was pressed" << std::endl;
}