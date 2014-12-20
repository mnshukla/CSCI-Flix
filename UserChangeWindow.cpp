#include "UserChangeWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <iostream>
#include <QString>
#include <QCloseEvent>
#include "LoginWindow.h"
//#include "UserMenu.h"
#include "md5.h"

using namespace std;

UserChangeWindow::UserChangeWindow (User *_user, Netflix *netflix1)
{
	user = _user;
	netflix = netflix1;

	QVBoxLayout *mainLayout = new QVBoxLayout;

	login = new QLineEdit;
	address = new QLineEdit;
	credit_card_info = new QLineEdit;
	password = new QLineEdit;

	QFormLayout *fl = new QFormLayout;
	fl->addRow("&Login", login);
	//fl->addRow("&Name", name);
	fl->addRow("&Password", password);
	fl->addRow("Address", address);
	fl->addRow("Credit Card Number", credit_card_info);
	QLabel *welcome = new QLabel ("Change/ Re-Enter Your Information");
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
	connect (password, SIGNAL(returnPressed()), confirmButton, SIGNAL(clicked()));

//	mainLayout->addWidget(new QLabel ("Please sign up for CSCI 104-Flix"));
	mainLayout->addLayout(buttonLayout);
	setLayout (mainLayout);

}

void UserChangeWindow::confirmPressed ()
{
	string _login = login->text().toStdString();
	//string _name = name->text().toStdString();
	string _password = password->text().toStdString();
	string _address = address->text().toStdString();
	string _credit_card_info = credit_card_info->text().toStdString();
	string hashed_password = md5(_password);
	string hashed_credit = md5(_credit_card_info);
	user->setPassword(hashed_password);
	user->setAddress(_address);
	user->setCreditCardInfo(hashed_credit);
	close();
	UserMenu *um = new UserMenu(netflix, _login);
	um->show();

}

void UserChangeWindow::cancelPressed()
{
	string _login = login->text().toStdString();
	close();
	UserMenu *um = new UserMenu(netflix, _login);
	um->show();
}
