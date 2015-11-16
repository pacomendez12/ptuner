#include <ptuner_window.h>
#include <iostream>

#define TAG "MAIN_WINDOW"

Main_window::Main_window()
: m_button("This is a button"), m_box(Gtk::ORIENTATION_VERTICAL)
{
	set_border_width(10);
	set_position(Gtk::WIN_POS_CENTER);
	set_default_size(400, 500);
	set_title("Ptuner:: The open source Guitar Tuner");


	add(m_box);


	m_button.signal_clicked().connect(sigc::mem_fun(*this, 
				&Main_window::on_button_clicked));

	m_button.signal_enter().connect(sigc::mem_fun(*this, 
				&Main_window::on_mouse_enter));

	add(m_button);

	m_button.show();

	show_all_children();

}

Main_window::~Main_window() 
{
}

void
Main_window::on_button_clicked() 
{
	std::cout << "button clicked" << std::endl;
}

void
Main_window::on_mouse_enter()
{
	std::cout << "Mouse entered" << std::endl;
}




int main(int argc, char * argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, 
			"org.paco.ptuner");

	Main_window mw;

	auto refBuilder = Gtk::Builder.create();
	try {
		refBuilder.add_from_file("./data/ptuner_main_window.glade");
	} catch (const Glib::FileError &ex) {
		mw.l.slog(TAG, "%s", ex.what());
	} catch (const Glib::MarkupError &ex) {
		mw.l.slog(TAG, "%s", ex.what());
	}
	
	return app->run(window);
}
