#ifndef USERCHANGEWINDOW_H
#define USERCHANGEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCloseEvent>
#include "Netflix.h"
#include "UserMenu.h"
 #include <QMessageBox>

class UserChangeWindow : public QWidget
{
	
	Q_OBJECT

	public:
		UserChangeWindow (User *_user, Netflix *netflix1);

	public slots:
		void confirmPressed();
		void cancelPressed();

	private:
		QPushButton *confirmButton, *cancelButton;
		QLineEdit *login, *address, *credit_card_info, *password;
		User *user;
		Netflix *netflix;

};

#endif