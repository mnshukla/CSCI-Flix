#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <iostream>
#include <QString>
#include <QCloseEvent>
#include <QString>
#include "MovieMenu.h"
#include "UserMenu.h"

using namespace std;

MovieMenu::MovieMenu (Netflix *netflix1, Movie* _movie, User *_user)
{
	netflix = netflix1;
	movie = _movie;
	user = _user;

	QVBoxLayout *mainLayout = new QVBoxLayout;

	keywordGroupBox = new QGroupBox(tr("Movie Info"));
	QHBoxLayout *klayout = new QHBoxLayout;
	klayout->addWidget(new QLabel (" "));

	string keywords = movie->getAllKeywords().printKeyOnly();
	QString qstr = QString::fromStdString(keywords);
	QLabel *keyWord = new QLabel (qstr);
	klayout->addWidget(keyWord);

	keywordGroupBox->setLayout(klayout);

	buttonGroupBox = new QGroupBox;
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	nextButton = new QPushButton("&Next Movie");
	addButton = new QPushButton("&Add to my Queue");
	returnButton = new QPushButton("&Return to Main Menu");
	buttonLayout->addWidget(nextButton);
	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(returnButton);
	buttonGroupBox->setLayout(buttonLayout);

	string movie_title = movie->getTitle();
	QString qstr1 = QString::fromStdString(movie_title);
	QLabel *movieTitle = new QLabel (qstr1);
	movieTitle->setAlignment(Qt::AlignCenter);

	connect (nextButton, SIGNAL(clicked()), this, SLOT(nextPressed()));
	connect (addButton, SIGNAL(clicked()), this, SLOT(addPressed()));
	connect (returnButton, SIGNAL(clicked()), this, SLOT(returnPressed()));

	mainLayout->addWidget(movieTitle);
	mainLayout->addWidget(keywordGroupBox);
	mainLayout->addWidget(buttonGroupBox);

	setLayout(mainLayout);

}

void MovieMenu::nextPressed()
{

	Movie* next_movie = netflix->nextMovie();
	if (next_movie->getTitle() == "Blah")
	{
 		nextButton->setEnabled(false);
 		QMessageBox msg;
		msg.setText("No other movies!");
		msg.exec();
	}
	else
	{
		MovieMenu *nm = new MovieMenu(netflix, next_movie, user);
		//this->hide();
		close();
		nm->show();
	}

}

void MovieMenu::addPressed()
{
	netflix->addMovie(user->getID());
}

void MovieMenu::returnPressed()
{
	UserMenu* um = new UserMenu(netflix, user->getID());
	//this->hide();
	close();
	um->show();
}