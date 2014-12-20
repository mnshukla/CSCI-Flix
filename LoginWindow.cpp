#include "LoginWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <iostream>
#include <QString>
#include <QCloseEvent>
#include "UserMenu.h"
#include "md5.h"

using namespace std;

LoginWindow::LoginWindow (Netflix *netflix1)
{
	// Layout functions
	// addWidget(QWidget*)
	// addLayout(QLayout*)
	// Widget functions
	// setLayout (QLayout*)
	// show();
	// hide();

	netflix = netflix1;

	QVBoxLayout *mainLayout = new QVBoxLayout;

	login = new QLineEdit;
	password = new QLineEdit;
	//newUser = new QLineEdit;
	//password = new QLineEdit;

	QFormLayout *fl = new QFormLayout;
	fl->addRow("&Login", login);
	fl->addRow("&Password", password);
	//fl->addRow("&New User", newUser);
	//fl->addRow("&Password", password);
	QLabel *welcome = new QLabel ("Welcome to CSCI 104-Flix");
	welcome->setAlignment(Qt::AlignCenter);

	mainLayout->addWidget (welcome);
	mainLayout->addLayout(fl);

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	quitButton = new QPushButton ("&Quit"); // &(letter) underlines letter and if you do alt+(letter) it will click that button
	newUserButton = new QPushButton ("&New User");
	loginButton = new QPushButton("&Login");

	buttonLayout->addWidget(loginButton);
	buttonLayout->addWidget (newUserButton);
	buttonLayout->addWidget(quitButton);

	connect (loginButton, SIGNAL(clicked()), this, SLOT(loginPressed()));
	connect (newUserButton, SIGNAL(clicked()), this, SLOT(newUserPressed()));
	connect (quitButton, SIGNAL(clicked()), this, SLOT(quitPressed()));
	connect (password, SIGNAL(returnPressed()), loginButton, SIGNAL(clicked()));

	//connect(password, SIGNAL(returnPressed()), this, SLOT(loginPressed()));

	// mainLayout->addWidget (new QLabel ("Welcome to CSCI 104-Flix"));
	mainLayout->addLayout(buttonLayout);
	setLayout (mainLayout);


}

void LoginWindow::loginPressed()
{
	string login_name = login->text().toStdString();
	string temp_password = password->text().toStdString();
	string hashed_password = md5(temp_password);

	// cout << "Login: " << login_name << endl;
	// do shit for password 
	// do something like 
	// Netflix Backend get user information
	if(netflix->login(login_name, hashed_password))
	{
		//this->hide();
		close();
		UserMenu *um = new UserMenu(netflix, login_name);
		um->show();
	}
	else
	{
		// LoginWindow *lw = new LoginWindow(netflix);
		// this->hide();
		// lw->show();
		QMessageBox msg;
		msg.setText("Invalid Username or Password! Try again!");
		msg.exec();
	}

	//go to user menu
}

void LoginWindow::newUserPressed()
{
	// string new_user_name = newUser->text().toStdString();
	// cout << "Enter your desired user name: " << new_user_name << endl;
	NewUserWindow *nw = new NewUserWindow(netflix);
	nw->show();
	//this->hide();
	close();
//	netflix->createNewUser();
	//netflix->createNewUser();

	// pop up new user window 
}

void LoginWindow::quitPressed()
{
	//cout << "Quit was pressed" << endl;
	netflix->update_user_file();
	close ();
}