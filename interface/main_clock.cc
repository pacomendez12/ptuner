#include "clock.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

int main(int argc, char** argv)
{
   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

   Gtk::Window win;
   win.set_title("Cairomm Clock");
   win.width(500);
   win.width(300);

   Clock c;
   win.add(c);
   c.show();

   return app->run(win);
}