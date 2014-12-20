#include "ViewAllRatingsWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QString>
#include <QFormLayout>
#include <sstream>

ViewAllRatingsWindow::ViewAllRatingsWindow(User* _user, Netflix* _netflix)
{
	user = _user;
	netflix = _netflix;

	QVBoxLayout *mainLayout = new QVBoxLayout;

	QGroupBox *ratingsBox = new QGroupBox(tr("All Ratings"));
	QVBoxLayout *ratingsLayout = new QVBoxLayout;
	ratingsLayout->addWidget(new QLabel(" "));

	confirmButton = new QPushButton("&Confirm");
	cancelButton = new QPushButton("&Cancel");

	// int map_size = user->ratings_map()->size();
	// for (int i = 0; i < map_size; i++)
	// {

	// }
	Map<string, int>::Iterator mit = user->rating_map()->begin();
	for (mit; mit != user->rating_map()->end(); ++mit)
	{
		string movie_info = "";
		string movie_buffer = (*mit).first;
		int movie_num = (*mit).second;
		stringstream ss;
		ss << movie_num;
		string movie_rating = ss.str();
		movie_info = movie_buffer + " " + movie_rating;
		// cout << movie_buffer->getTitle() << endl;
		QString qstr = QString::fromStdString(movie_info);
		QLabel *movie = new QLabel (qstr);
		ratingsLayout->addWidget(movie);
	}
	movie_title = new QLineEdit;
	new_rating = new QLineEdit;
	QFormLayout *fl = new QFormLayout;
	fl->addRow("&Enter Movie Title", movie_title);
	fl->addRow("&Enter New Rating from 1-5", new_rating);

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(confirmButton);
	buttonLayout->addWidget(cancelButton);

	ratingsBox->setLayout(ratingsLayout);
	mainLayout->addWidget(ratingsBox);
	mainLayout->addLayout(fl);
	mainLayout->addLayout(buttonLayout);

	setLayout(mainLayout);

	connect (confirmButton, SIGNAL(clicked()), this, SLOT(confirmPressed()));
	connect (cancelButton, SIGNAL(clicked()), this, SLOT(cancelPressed()));

}

void ViewAllRatingsWindow::confirmPressed()
{
	string movie_title_temp = movie_title->text().toStdString();
	string temp_movie_rating = new_rating->text().toStdString();
	int movie_rating;
	istringstream ss(temp_movie_rating);
	ss >> movie_rating;

	user->rating_map()->remove(movie_title_temp);
	user->rating_map()->add(movie_title_temp, movie_rating);
	cancelPressed();
}

void ViewAllRatingsWindow::cancelPressed()
{
	this->hide();
	UserMenu *uw = new UserMenu(netflix, user->getID());
	uw->show();
}
