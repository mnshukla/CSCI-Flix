#include <QApplication>
#include "LoginWindow.h"
// #include "NewUserWindow.h"
// #include "UserMenu.h"
// #include "MovieMenu.h"
#include "Netflix.h"
#include "RatingsWindow.h"

int main (int argc, char* argv[])
{
	QApplication app(argc, argv);
	Netflix *netflix = new Netflix();
	netflix->read_file(argv[1]);
	LoginWindow w(netflix);
	// NewUserWindow nw(netflix);
	// nw.show();
	// UserMenu um;
	// MovieMenu mm;

	w.show();
	//RatingsWindow rw;
	//rw.show();
	// nw.show();
	// um.show();
	// mm.show();
	
	return app.exec();
}
