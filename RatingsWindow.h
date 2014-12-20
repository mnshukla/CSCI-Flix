#ifndef RATINGSWINDOW_H
#define RATINGSWINDOW_H

#include <QWidget>
#include <QPushButton>
// #include <QPixMap>
#include <QIcon>
#include <QGroupBox>
#include <QHBoxLayout>
#include <iostream>
#include "Movie.h"
#include "User.h"

using namespace std;

class RatingsWindow : public QWidget
{
	
	Q_OBJECT

	public:
		RatingsWindow(string _rated_movie, User* _current_user);

	public slots:
		void pressed1();
		void pressed2();
		void pressed3();
		void pressed4();
		void pressed5();

	private:
		QPushButton *skipButton, *button1, *button2, *button3, *button4, *button5;
		QGroupBox *ratingsBox;
		string rated_movie;
		User* current_user;


};

#endif