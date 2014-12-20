#include "UserMenu.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <iostream>
#include <QString>
#include <QCloseEvent>
#include "LoginWindow.h"
#include "MovieMenu.h"
#include "RatingsWindow.h"
#include "UserChangeWindow.h"
#include "ViewAllRatingsWindow.h"

using namespace std;

UserMenu::UserMenu (Netflix *netflix1, string userID)
{
	netflix = netflix1;
	user = netflix->getUser(userID);
	movie = NULL;

	QVBoxLayout *mainLayout = new QVBoxLayout;

	currentMovieGroupBox = new QGroupBox(tr("Your Current Movie"));
	QVBoxLayout *CMlayout = new QVBoxLayout;
	returnButton = new QPushButton("&Return Movie");
	current_movie_title = " ";
	if (!user->currentMovie() == NULL)
	{
		current_movie_title = user->currentMovie()->getTitle();
	}
	QString qstr = QString::fromStdString(current_movie_title);
	current_movie = new QLabel(qstr);
	// CMlayout->addWidget(new QLabel (qstr));
	CMlayout->addWidget(current_movie);
	CMlayout->addWidget(returnButton);
	currentMovieGroupBox->setLayout(CMlayout);

	movieQueueGroupBox = new QGroupBox(tr("Your Movie Queue"));
	movieQueueP2GroupBox = new QGroupBox;
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	QHBoxLayout *MQlayout = new QHBoxLayout;
	rentButton = new QPushButton("&Rent Movie: $2");
	removeButton = new QPushButton("&Delete from Queue");
	moveButton = new QPushButton("&Move to back of Queue");
	front_of_queue_movie_title = " ";
	if (!user->movieQueue()->isEmpty())
	{
		front_of_queue_movie_title = user->movieQueue()->peekFront()->getTitle();
	}
	qstr = QString::fromStdString(front_of_queue_movie_title);
	front_movie = new QLabel(qstr);
	// MQlayout->addWidget(new QLabel (qstr));
	MQlayout->addWidget(front_movie);
	buttonLayout->addWidget(rentButton);
	buttonLayout->addWidget(removeButton);
	buttonLayout->addWidget(moveButton);
	movieQueueGroupBox->setLayout(MQlayout);
	movieQueueP2GroupBox->setLayout(buttonLayout);

	searchMovieGroupBox = new QGroupBox(tr("Search for a Movie"));
	searchMovieP2GroupBox = new QGroupBox;
	QHBoxLayout *SMlayout = new QHBoxLayout;
	QHBoxLayout *searchLayout = new QHBoxLayout;
	QFormLayout* fl = new QFormLayout;
	search = new QLineEdit;
	fl->addRow("&Search", search);
	SMlayout->addLayout(fl);
	searchTButton = new QPushButton("Search by &Title");
	searchKButton = new QPushButton("Search by &Keyword");
	searchAButton = new QPushButton("Search by &Actor");
	searchLayout->addWidget(searchTButton);
	searchLayout->addWidget(searchKButton);
	searchLayout->addWidget(searchAButton);
	searchMovieGroupBox->setLayout(SMlayout);
	searchMovieP2GroupBox->setLayout(searchLayout);

	logoutButton = new QPushButton("&Logout");
	changeButton = new QPushButton("&Change Personal Information");
	modifyButton = new QPushButton("&View and Modify all Movie Ratings");

	string welcome_tag = "Welcome to CSCI 104-Flix " + user->getName() + " (" + user->getID() + ")";
	qstr = QString::fromStdString(welcome_tag);

	QLabel *welcome = new QLabel (qstr);
	welcome->setAlignment(Qt::AlignCenter);

	connect (returnButton, SIGNAL (clicked()), this, SLOT(returnPressed()));
	connect (searchTButton, SIGNAL(clicked()), this, SLOT(searchByTPressed()));
	connect (searchKButton, SIGNAL(clicked()), this, SLOT(searchByKPressed()));
	connect (searchAButton, SIGNAL(clicked()), this, SLOT(searchByKPressed()));
	connect (logoutButton, SIGNAL(clicked()), this, SLOT(logoutPressed()));
	connect (changeButton, SIGNAL(clicked()), this, SLOT(changePressed()));	
	connect (modifyButton, SIGNAL(clicked()), this, SLOT(modifyPressed()));		
	connect (rentButton, SIGNAL (clicked()), this, SLOT(rentPressed()));
	connect (removeButton, SIGNAL(clicked()), this, SLOT(deletePressed()));
	connect (moveButton, SIGNAL (clicked()), this, SLOT(movePressed()));
	connect (search, SIGNAL(returnPressed()), searchTButton, SIGNAL(clicked()));
	//connect (search, SIGNAL(returnPressed()), searchKButton, SIGNAL(clicked()));

	mainLayout->addWidget(welcome);
	mainLayout->addWidget(currentMovieGroupBox);
	mainLayout->addWidget(movieQueueGroupBox);
	mainLayout->addWidget(movieQueueP2GroupBox);
	mainLayout->addWidget(searchMovieGroupBox);
	mainLayout->addWidget(searchMovieP2GroupBox);
	mainLayout->addWidget(modifyButton);
	mainLayout->addWidget(changeButton);
	mainLayout->addWidget(logoutButton);
	setLayout(mainLayout);
}

void UserMenu::returnPressed ()
{
	//cout << "Return pressed" << endl;
	if (!netflix->returnMovie(user->getID()))
	{
		returnButton->setEnabled(false);
		QMessageBox msg;
		msg.setText("No movie rented! Cannot return!");
		msg.exec();
	}
	else
	{
		//this->hide();
		close();
		// RatingsWindow *rw = new RatingsWindow(netflix, user->currentMovie(), user);
		UserMenu *um = new UserMenu(netflix, user->getID());
		um->show();
		//rw->show();
		// QString qstr = QString::fromStdString(current_movie_title);
		// current_movie->setText(qstr);
	}
}

void UserMenu::searchByTPressed()
{
//	cout << "Search by Title pressed" << endl;
	string search_movie_title = search->text().toStdString();
	transform(search_movie_title.begin(), search_movie_title.end(), search_movie_title.begin(), ::tolower);

	if(netflix->searchByTitle(search_movie_title))
	{
		movie = netflix->getMovie(search_movie_title);
		MovieMenu *m = new MovieMenu(netflix, movie, user);
		//this->hide();
		close();
		m->show();
	}
	else
	{
		// pop up error
	}

	//cout << "Searched Term: " << search_movie_title << endl;
}

void UserMenu::searchByKPressed ()
{
	//cout << "Search by Keyword pressed" << endl;
	string search_movie_keyword = search->text().toStdString();
	if(netflix->searchByKeyword(search_movie_keyword))
	{

		// MovieMenu *m = new MovieMenu(netflix, movie);
		Movie* keyword_movie = netflix->keywordMovie(search_movie_keyword);
		MovieMenu *m = new MovieMenu(netflix, keyword_movie, user);
		//this->hide();
		close();
		m->show();
	}
	else
	{

	}

}

void UserMenu::logoutPressed()
{
	// cout << "Logout pressed" << endl;
	LoginWindow *lw = new LoginWindow(netflix);
	//this->hide();
	close();
	lw->show();	
}

void UserMenu::rentPressed ()
{
	// cout << "Rent Movie pressed" << endl;

	if (netflix->rentMovie(user->getID()))
	{
		//this->hide();
		close();
		// increase user total charges
		user->addCharge();
		QMessageBox msg;
		string charges = "Total Charges: $" + user->getCharges() ;
		QString qstr = QString::fromStdString(charges);
		msg.setText(qstr);
		msg.exec();
		UserMenu *um = new UserMenu(netflix, user->getID());
		um->show();	
		// QString qstr = QString::fromStdString(front_of_queue_movie_title);
		// front_movie->setText(qstr);
	}
	else
	{
		rentButton->setEnabled(false);
		QMessageBox msg;
		msg.setText("Movie already rented! Cannot rent!");
		msg.exec();
	}
}

void UserMenu::deletePressed()
{
	if (netflix->deleteMovie(user->getID()))
	{
		//this->hide();
		close();
		UserMenu *um = new UserMenu(netflix, user->getID());
		um->show();
	}
	else
	{
		removeButton->setEnabled(false);
		QMessageBox msg;
		msg.setText("No movies in queue! Cannot delete!");
		msg.exec();

	}
	// cout << "Delete movie pressed" << endl;
}

void UserMenu::movePressed ()
{

	if(netflix->moveMovie(user->getID()))
	{
		//this->hide();
		close();
		UserMenu *um = new UserMenu(netflix, user->getID());
		um->show();
	}
	else
	{
		moveButton->setEnabled(false);
		QMessageBox msg;
		msg.setText("No movies in queue! Cannot delete!");
		msg.exec();
	}

}

void UserMenu::changePressed()
{
	UserChangeWindow *cw = new UserChangeWindow(user, netflix);
	this->hide();
	cw->show();
}

void UserMenu::modifyPressed()
{
	this->hide();
	ViewAllRatingsWindow *vw = new ViewAllRatingsWindow(user, netflix);
	vw->show();
}