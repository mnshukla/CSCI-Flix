#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCloseEvent>
#include "Netflix.h"
#include "NewUserWindow.h"
 #include <QMessageBox>

class LoginWindow : public QWidget
{
	
	Q_OBJECT

	public:
		LoginWindow (Netflix *netflix1);

	public slots:
		void loginPressed ();
		void newUserPressed();
		void quitPressed();

	private:
		QPushButton *quitButton, *loginButton, *newUserButton;
		QLineEdit *login, *password; //*newUser;//, *password;
		Netflix *netflix;

};

#endif
