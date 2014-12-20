#include <string>
#include <iostream> 
#include "User.h"
#include <sstream>

using namespace std; 

User::User(string ID, string name)
{
	
	user_id = ID;
	user_name = name;
	user_movie_queue = new Queue<Movie*>;
	number_of_movies = 0;
	rented_movie = NULL;
	user_ratings_map = new Map<string, int>;
	address = "";
	credit_card_info = "";
	total_charges = 0;

}

User::User(const User & other)
{

	user_id = other.user_id;
	user_name = other.user_name;

}


User::~User()
{

	if (rented_movie != NULL)
	{
		delete rented_movie;
	}

	delete user_movie_queue;
	// delete all movies in queue?
	
}

string User::getID () const 
{

	return user_id;

}

string User::getName () const
{

	return user_name;

}

void User::addCharge () 
{
	total_charges += 2;
}

void User::setAddress(string _address)
{
	address = _address;
}

void User::setCreditCardInfo (string _credit_card_info)
{
	credit_card_info = _credit_card_info;
}

void User::setPassword (string _password)
{
	password = _password;
}

string User::getAddress() const
{
	return address;
}

string User::getHash() const
{
	return password;
}

string User::getCreditHash() const
{
	return credit_card_info;
}

string User::getCharges () const
{
	stringstream ss;
	ss << total_charges;
	string charges;
	ss >> charges;

	return charges;
}

Queue<Movie*> * User::movieQueue ()
{
	return user_movie_queue;
}

Map<string, int> * User::rating_map()
{
	return user_ratings_map;
}

void User::rentMovie (Movie *m)
{
	if (rented_movie == NULL)
	{
		rented_movie = m;
	}

}


void User::returnMovie ()
{
	if (rented_movie != NULL)
	{
		delete rented_movie;
		rented_movie = NULL;
	}
}


Movie* User::currentMovie () const
{
	return rented_movie;
}
