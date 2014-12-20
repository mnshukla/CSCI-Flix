#ifndef NEWUSERWINDOW_H
#define NEWUSERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCloseEvent>
#include "Netflix.h"
 #include <QMessageBox>

class Netflix;

class NewUserWindow : public QWidget
{
	
	Q_OBJECT

	public:
		NewUserWindow (Netflix *netflix1);

	public slots:
		void confirmPressed();
		void cancelPressed();

	private:
		QPushButton *confirmButton, *cancelButton;
		QLineEdit *login, *name, *address, *credit_card_info, *password;
		Netflix *netflix;

};

#endif