#include "RatingsWindow.h"
#include <QPixmap>

using namespace std;

RatingsWindow::RatingsWindow (string _rated_movie, User* _current_user) 
{
	rated_movie = _rated_movie;
	current_user = _current_user;
	// cout << rated_movie->getTitle() << endl;
	// cout << current_user->getID() << endl;

	QPixmap starIcon("/home/student/project_mshukla/staricon.png");
	QIcon buttonIcon(starIcon);

	button1 = new QPushButton();
	button2 = new QPushButton();
	button3 = new QPushButton();
	button4 = new QPushButton();
	button5 = new QPushButton();
	skipButton = new QPushButton("&Skip Ratings for now");

	button1->setIcon(buttonIcon);
	//button1->setIconSize(starIcon.rect().size());
	button2->setIcon(buttonIcon);
	//button2->setIconSize(starIcon.rect().size());
	button3->setIcon(buttonIcon);
	//button3->setIconSize(starIcon.rect().size());
	button4->setIcon(buttonIcon);
	//button4->setIconSize(starIcon.rect().size());
	button5->setIcon(buttonIcon);
	//button5->setIconSize(starIcon.rect().size());

	QHBoxLayout *ratingsLayout = new QHBoxLayout;

	ratingsLayout->addWidget(button1);
	ratingsLayout->addWidget(button2);
	ratingsLayout->addWidget(button3);
	ratingsLayout->addWidget(button4);
	ratingsLayout->addWidget(button5);
	//ratingsLayout->addWidget(skipButton);

	QHBoxLayout *skipLayout = new QHBoxLayout;
	skipLayout->addWidget(skipButton);

	QGroupBox *skipBox = new QGroupBox;
	skipBox->setLayout(skipLayout);

	ratingsBox = new QGroupBox(tr("Rate the movie!"));
	ratingsBox->setLayout(ratingsLayout);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(ratingsBox);
	mainLayout->addWidget(skipBox);

	connect (button1, SIGNAL(clicked()), this, SLOT(pressed1()));
	connect (button2, SIGNAL(clicked()), this, SLOT(pressed2()));
	connect (button3, SIGNAL(clicked()), this, SLOT(pressed3()));
	connect (button4, SIGNAL(clicked()), this, SLOT(pressed4()));
	connect (button5, SIGNAL(clicked()), this, SLOT(pressed5()));
	connect (skipButton, SIGNAL(clicked()), this, SLOT(close()));

	setLayout(mainLayout);

}

void RatingsWindow::pressed1()
{
	current_user->rating_map()->add(rated_movie, 1);
	//cout << current_user->getID() << endl;
	//cout << rated_movie->getTitle() << endl;
	this->hide();
}

void RatingsWindow::pressed2()
{
	current_user->rating_map()->add(rated_movie, 2);
	this->hide();
}

void RatingsWindow::pressed3()
{
	current_user->rating_map()->add(rated_movie, 3);
	this->hide();
}

void RatingsWindow::pressed4()
{
	current_user->rating_map()->add(rated_movie, 4);
	this->hide();
}

void RatingsWindow::pressed5()
{
	current_user->rating_map()->add(rated_movie, 5);
	this->hide();
}