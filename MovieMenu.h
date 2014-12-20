#ifndef MOVIEMENU_H
#define MOVIEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCloseEvent>
#include <QGroupBox>
#include "Netflix.h"
#include <QMessageBox>
#include "RatingsWindow.h"

class MovieMenu : public QWidget
{

	Q_OBJECT

public:
	MovieMenu(Netflix *netflix1, Movie* _movie, User* _user);

public slots:
	void nextPressed();
	void addPressed();
	void returnPressed();

private:
	QGroupBox *keywordGroupBox, *buttonGroupBox;
	QPushButton *nextButton, *addButton, *returnButton;
	Netflix *netflix;
	Movie* movie;
	User* user;
};

#endif