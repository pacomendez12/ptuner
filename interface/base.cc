#include <gtkmm.h>
//g++ base.cc -o base `pkg-config gtkmm-3.0 --cflags --libs` 
int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

  Gtk::Window window;

  window.set_default_size(900, 500);

  return app->run(window);
}