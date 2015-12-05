#include <gui/ProyectImplementation.h>
#include <gtkmm/application.h>

using namespace std;

int main(int argc, char *argv[]){
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	Interface window;
	window.set_default_size(800,600);
	
	// Shows the window and returns when it is closed.
	return app->run(window);
}