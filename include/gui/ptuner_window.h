#ifndef PTUNER_WINDOW_H

#define PTUNER_WINDOW_H

#include <gtkmm.h>

class Main_window : public Gtk::Window
{
	public:
		Main_window();
		~Main_window();

	protected:
		void on_button_clicked();
		void on_mouse_enter();

		Gtk::Button m_button;

	private:
		//widgets
		Gtk::Box m_box;

		Glib::RefPtr<Gtk::Builder> ref_builder;

};

#endif /* end of include guard: PTUNER_WINDOW_H */
