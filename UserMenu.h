#ifndef USERMENU_H
#define USERMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCloseEvent>
#include <QGroupBox>
#include "Netflix.h"
#include <QLabel>
#include <QMessageBox>

class UserMenu : public QWidget
{
	Q_OBJECT

public:
		UserMenu (Netflix *netflix1, string userLogin);

public slots:
	void returnPressed ();
	void searchByTPressed();
	void searchByKPressed();
	void logoutPressed();
	void rentPressed();
	void deletePressed();
	void movePressed();
	void changePressed();
	void modifyPressed();


private:
	QGroupBox *currentMovieGroupBox, *movieQueueGroupBox, *searchMovieGroupBox, *movieQueueP2GroupBox, *searchMovieP2GroupBox;
	QPushButton *returnButton, *rentButton, *removeButton, *moveButton, *searchTButton, *searchKButton, *searchAButton, *logoutButton, *changeButton, *modifyButton;
	QLineEdit *search;
	Netflix *netflix;
	User *user;
	Movie* movie;
	string current_movie_title, front_of_queue_movie_title;
	QLabel *current_movie, *front_movie;
};

#endif