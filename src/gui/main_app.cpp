#include <gtkmm.h>

int main(int argc, char * argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.paco.ptuner");

	Gtk::Window window;
	window.set_default_size(400, 500);
	

	return app->run(window);
}
