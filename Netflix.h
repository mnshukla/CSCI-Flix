#ifndef NETFLIX_H
#define NETFLIX_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "User.h"
#include "Movie.h"
//#include "UserMenu.h"
// #include "LoginWindow.h"
#include "NewUserWindow.h"
#include <QMessageBox>
#include "RatingsWindow.h"
// #include "UserMenu.h"
// #include "MovieMenu.h"


using namespace std;

class Netflix
{
	
	public:
		Netflix();
		~Netflix();
		void read_file(string file_name);
		void read_user_file (string user_file);
		void read_movie_file (string movie_file);
		void first_menu_text();
		void first_menu ();
		void logged_in_menu_text ();
		void logged_in_menu (string user_id);
		void penultimate_menu ();
		void view_queue_menu_text();
		void final_menu ();
		void last_menu();
		void update_user_file ();
		User* getUser(string userID);
		Movie* getMovie(string movie_title);
	//	int rateMovie(int rating_number);



		bool login (string loginID, string);
		bool createNewUser(string login, string name, string, string, string);
		bool returnMovie(string user_id);
		bool rentMovie(string user_id);
		bool deleteMovie(string user_id);
		bool moveMovie(string user_id);
		bool searchByTitle(string movie);
		bool searchByKeyword(string keyword);
		Movie* keywordMovie(string movie_keyword);
		Movie* nextMovie();
		void addMovie(string user_id);

	private:
		Map<string, User*> user_map; // holds user info
		Map<string, Movie*> movie_map; // holds movie info
		Map<string, Set<Movie*>*> keyword_lookup_map; // used to look up keywords in system
		string user_file = "";
		Set<Movie*>::Iterator it;
		Set<Movie*>* temp_set;
		Movie* add_movie;
		int keyword_counter;

};


#endif 