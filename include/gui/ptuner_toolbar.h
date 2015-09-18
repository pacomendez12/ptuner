#ifndef PTUNER_TOOLBAR_H

#define PTUNER_TOOLBAR_H

#include <gtkmm.h>


class ptuner_toolbar : Gtk::MenuBar
{
public:
	ptuner_toolbar();
	~ptuner_toolbar();

protected:
	//handlers
	//sub menu [file]
	void on_menu_file_quit();

	//sub menu [edit]
	void on_menu_edit_preferences();
private:
	/* data */
};


#endif /* end of include guard: PTUNER_TOOLBAR_H */
