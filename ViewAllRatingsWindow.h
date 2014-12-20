#ifndef VIEWALLRATINGS_H
#define VIEWALLRATINGS_H

#include <iostream>
#include <QPushButton>
#include <QLineEdit>
#include "UserMenu.h"

using namespace std;

class ViewAllRatingsWindow : public QWidget
{
	
	Q_OBJECT

	public:
		ViewAllRatingsWindow(User* _user, Netflix *_netflix);

	public slots:
		void confirmPressed();
		void cancelPressed();

	private:
		QPushButton *confirmButton, *cancelButton;
		QLineEdit *movie_title, *new_rating;
		User *user;
		Netflix *netflix;

};




#endif