#include <ptuner_toolbar.h>

ptuner_toolbar::ptuner_toolbar()
{
	ref_builder = Gtk::Builder::create();

	Glib::RefPtr<Gio::SimpleActionGroup> refAction =
		Gio::SimpleActionGroup::create();

	refAction->add_action("quit", sigc::mem_fun(*this, 
				&ptuner_toolbar::on_menu_file_quit));

	insert_action_group("toolbar", refAction);

	Glib::ustring ui_string = 
		"<interface>"
		"	<menu id='ptuner-menu'>"
		"		<submenu>"
		"			<attribute name='label' translatable='yes'>_File</attribute>"
		"			<section>"
		"				<item>"
		"					<attribute name='label' translatable='yes'>_Quit</attribute>"
		"					<attribute name='action'>toolbar.quit</attribute>"
		"					<attribute name='accel'>&lt;Primary&gt;q</attribute>"
		"				</item>"
		"			</section>"
		"		</submenu>"
		"	</menu>"
		"</interface>";

	try {
		ref_builder->add_from_string(ui_string);
	} catch(const Glib::Error & ex)
	{
		std::cerr << "Building menus failed" << ex.what();
	}

	Glib::RefPtr<Glib::Object> object = ref_builder->get_object("ptuner-menu");
	Glib::RefPtr<Gio::Menu> gmenu =
		Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
	if (!gmenu) {
		g_warning("ptuner-menu not found");
	}

	Gtk::MenuBar *menu_bar = Gtk::manage(new Gtk::MenuBar(gmenu));


}

void
ptuner_toolbar::on_menu_edit_preferences()
{

}

void
ptuner_toolbar::on_menu_file_quit()
{
	Gtk::Main::quit();
}
