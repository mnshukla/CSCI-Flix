#include "NewUserWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <iostream>
#include <QString>
#include <QCloseEvent>
#include "LoginWindow.h"
#include "UserMenu.h"
#include "md5.h"

using namespace std;

NewUserWindow::NewUserWindow (Netflix *netflix1)
{
	netflix = netflix1;

	QVBoxLayout *mainLayout = new QVBoxLayout;

	login = new QLineEdit;
	name = new QLineEdit;
	address = new QLineEdit;
	credit_card_info = new QLineEdit;
	password = new QLineEdit;

	QFormLayout *fl = new QFormLayout;
	fl->addRow("&Login", login);
	fl->addRow("&Name", name);
	fl->addRow("&Password", password);
	fl->addRow("Address", address);
	fl->addRow("Credit Card Number", credit_card_info);
	QLabel *welcome = new QLabel ("Please sign up for CSCI 104-Flix");
	welcome->setAlignment(Qt::AlignCenter);

	mainLayout->addWidget(welcome);
	mainLayout->addLayout(fl);

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	confirmButton = new QPushButton ("&Confirm");
	cancelButton = new QPushButton ("&Cancel");

	buttonLayout->addWidget(confirmButton);
	buttonLayout->addWidget(cancelButton);

	connect (confirmButton, SIGNAL (clicked()), this, SLOT(confirmPressed()));
	connect (cancelButton, SIGNAL(clicked()), this, SLOT(cancelPressed()));
	connect (name, SIGNAL(returnPressed()), confirmButton, SIGNAL(clicked()));

//	mainLayout->addWidget(new QLabel ("Please sign up for CSCI 104-Flix"));
	mainLayout->addLayout(buttonLayout);
	setLayout (mainLayout);

}

void NewUserWindow::confirmPressed ()
{
	string _login = login->text().toStdString();
	string _name = name->text().toStdString();
	string _password = password->text().toStdString();
	string _address = address->text().toStdString();
	string _credit_card_info = credit_card_info->text().toStdString();
	string hashed_password = md5(_password);
	string hashed_credit = md5(_credit_card_info);
	if (!netflix->createNewUser(_login, _name, _address, hashed_credit, hashed_password))
		{
			QMessageBox msg;
			msg.setText("User already exists! Try again!");
			msg.exec();
			NewUserWindow *nw = new NewUserWindow(netflix);
			nw->show();
			//this->hide();
			close();
		}
	// cout << "User Login: " << _login << endl;
	// cout << "User Name: " << _name << endl;
	else
	{
		//this->hide();
		close();
		UserMenu *um = new UserMenu(netflix, _login);
		um->show();
	}

}

void NewUserWindow::cancelPressed()
{
	LoginWindow *lw = new LoginWindow(netflix);
	//this->hide();
	close();
	lw->show();
}
