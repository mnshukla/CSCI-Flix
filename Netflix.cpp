#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "Netflix.h"

using namespace std;

Netflix::Netflix()
{
	keyword_counter = 0;
}

Netflix::~Netflix()
{

}

bool Netflix::login (string loginID, string password)
{
	
	if (user_map.contains(loginID))
	{
		if (password == user_map.get(loginID)->getHash())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	else
	{
		return false;
	}

}

bool Netflix::createNewUser (string login, string name, string address, string credit, string password)
{

			if(user_map.contains(login))
			{
				return false;
			}

			User* add_user = new User(login, name);
			user_map.add(login, add_user);
			add_user->setPassword(password);
			add_user->setAddress(address);
			add_user->setCreditCardInfo(credit);
			return true;

}

bool Netflix::returnMovie(string user_id)
{
	if (user_map.get(user_id)->currentMovie() == NULL)
	{
		//cout << "\nYou do not have a rented movie at this time." << endl;
		return false;
	}
	else 
	{
		//cout << "\nYour rental " << user_map.get(user_id)->currentMovie()->getTitle() << " has been returned." << endl;
		//cout << " 1 " << user_map.get(user_id)->currentMovie()->getTitle() << endl;
		// cout << user_map.get(user_id)->getID() << endl;
		RatingsWindow *rw = new RatingsWindow(user_map.get(user_id)->currentMovie()->getTitle(), user_map.get(user_id));
		if (user_map.get(user_id)->rating_map()->contains(user_map.get(user_id)->currentMovie()->getTitle()))
		{
			QMessageBox msgBox;
			//msgBox.setWindowTitle("");
			msgBox.setText("Would you like to modify your ratings?");
			msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
			msgBox.setDefaultButton(QMessageBox::No);
			if(msgBox.exec() == QMessageBox::Yes)
			{
				user_map.get(user_id)->rating_map()->remove(user_map.get(user_id)->currentMovie()->getTitle());
				rw->show();
			}
			else 
			{
				msgBox.hide();
			}
		}
		else
		{
			rw->show();
		}
//		rw->show();
		user_map.get(user_id)->returnMovie();
		//rw->show();
		return true;
	}
}

bool Netflix::rentMovie(string user_id)
{
	if ((user_map.get(user_id)->currentMovie() == NULL) && (!user_map.get(user_id)->movieQueue()->isEmpty()))
	{
		//cout << "\nOrder: " << user_map.get(user_id)->movieQueue()->peekFront()->getTitle() << " complete." << endl;
		user_map.get(user_id)->rentMovie(user_map.get(user_id)->movieQueue()->peekFront());
		user_map.get(user_id)->movieQueue()->dequeue();
		return true;
	}
	else
	{
		// cout << "\nCannot order movie because ";
		// cout << user_map.get(user_id)->currentMovie()->getTitle() << " is currently checked out." << endl;
		// cout << "Please return the movie before ordering another one." << endl;
		return false;
	}
}

bool Netflix::deleteMovie(string user_id)
{
	if (!user_map.get(user_id)->movieQueue()->isEmpty())
	{
		user_map.get(user_id)->movieQueue()->dequeue();
		return true;
	}
	else
	{
		return false;
	}

}

bool Netflix::moveMovie(string user_id)
{
	if (!user_map.get(user_id)->movieQueue()->isEmpty())
	{
		Movie* replace_movie;
		replace_movie = user_map.get(user_id)->movieQueue()->peekFront();
		//replace_movie = user_map.get(user_id)->movieQueue()->peekFront();
		user_map.get(user_id)->movieQueue()->dequeue();
		user_map.get(user_id)->movieQueue()->enqueue(replace_movie);
		return true;
	}
	else
	{
		return false;
	}

}

bool Netflix::searchByTitle(string movie)
{

			transform(movie.begin(), movie.end(), movie.begin(), ::tolower);

			// check if movie is in map
			if (!movie_map.contains(movie))
			{
				QMessageBox msg;
				msg.setText("Movie does not exist!");
				msg.exec();
				return false;
			}
			else
			{
				// print keywords
				//cout << movie_map.get(movie)->getTitle() << endl;
				//movie_map.get(movie)->getAllKeywords().printKeyOnly();
				return true;
			}

}

bool Netflix::searchByKeyword(string user_keyword)
{

	transform(user_keyword.begin(), user_keyword.end(), user_keyword.begin(), ::tolower);
	if (!keyword_lookup_map.contains(user_keyword)) // check if keyword exists in map
	{
		QMessageBox msg;
		msg.setText("Keyword does not exist!");
		msg.exec();
		return false;
	}
	else 
	{
		return true;
	}

}

Movie* Netflix::keywordMovie (string user_keyword)
{
		temp_set = keyword_lookup_map.get(user_keyword);
		Set<Movie*>::Iterator movie_it = temp_set->begin();
		keyword_counter = 1;
		add_movie = (*movie_it);
		it = movie_it;

		return (*movie_it);
}

Movie* Netflix::nextMovie()
{

	if (keyword_counter > temp_set->size())
	{
		string temp = "Blah";
		Movie* temp_movie = new Movie(temp);

		return temp_movie;
		// break;
	}
	else if (keyword_counter <= temp_set->size())
	{
		++it;
		keyword_counter++;

		if (keyword_counter > temp_set->size())
		{
			string temp = "Blah";
			Movie* temp_movie = new Movie(temp);

			return temp_movie;
		}

		else
		{
			add_movie = (*it);
			return (*it);
		}
	}

}

void Netflix::addMovie(string user_id)
{
	user_map.get(user_id)->movieQueue()->enqueue(add_movie);
}

// string Netflix::rateMovie1(string movie_rental_title)
// {
// 	return movie_rental_title;
// }

// open initial input text file and open user and movie files 
void Netflix::read_file (string file)
{

	ifstream ifile;

	//Open from data folder 
	// string file_name = "\\data\\";

	// file_name.append(file);

	ifile.open(file.c_str());

	//checking if file failed
	if (ifile.fail()) {

		cerr << "\t\nError. Invalid Input File. Please try again." << endl;
		exit(0);
	}

	else 
	{
		string movie_file = "";

		getline(ifile, user_file, '\n');
		getline(ifile, movie_file);

		read_user_file(user_file);
		read_movie_file(movie_file);

	}

	ifile.close ();

}

// read and parse user file 
void Netflix::read_user_file (string user_file)
{

	ifstream ifile;
	ifile.open(user_file.c_str());

	if (ifile.fail())
	{
		cerr << "\t\nError. Invalid User File. Please try again." << endl;
		exit(0);
	}	
	else
	{
		string line = "";
		string indicator = "";
		string user_id = "";
		string user_name = "";
		string phrase = "";
		string buffer = "";
		string movie_title = "";
		string after_word = "";
		string movie_queue_title = "";
		int movie_rating;
		string rated_movie = "";
		User* add_user;
		string password = "";
		string credit = "";
		string address = "";

		while (getline(ifile,line))
		{
			stringstream ss(line);
			ss >> indicator; 

			if (indicator == "BEGIN")
			{
				ss >> after_word;
				if (after_word == "QUEUE")
				{
					// get movies in user's queue based on input file
					while(getline(ifile, line)) 
					{
						stringstream ss1(line);
						ss1 >> indicator;

						if (indicator == "END")
						{
							break;
						}
						else
						{
							getline(ss1, buffer, ' ');
							getline(ss1, movie_queue_title);
							indicator = indicator + " " + movie_queue_title;
							movie_queue_title = indicator;
							Movie* movie_in_queue;
							movie_in_queue = new Movie(movie_queue_title);
							add_user->movieQueue()->enqueue(movie_in_queue);
						}
					}
				}

				else if (after_word == "RATINGS")
				{
					while(getline(ifile, line))
					{
						stringstream ss2(line);
						ss2 >> indicator;

						if (indicator == "END")
						{
							break;
						}
						else
						{
							istringstream buff(indicator);
							buff >> movie_rating;
							// ss2 >> movie_rating;
							// cout << movie_rating << endl;
							getline(ss2, buffer, ' ');
							getline(ss2, rated_movie);
							//Movie* rated_movie_to_add;
							//rated_movie_to_add = new Movie(rated_movie);
							add_user->rating_map()->add(rated_movie, movie_rating);
							
						}
					}
				}
				else
				{
					user_id = after_word;
				}
			}
			else if (indicator == "NAME:")
			{
				user_name = line.erase(0,6);
				add_user = new User(user_id, user_name);
			}
			else if (indicator == "PASSWORD:")
			{
				password = line.erase(0,10);
				add_user->setPassword(password);
			}
			else if (indicator == "ADDRESS:")
			{
				address = line.erase(0,9);
				add_user->setAddress(address);
			}
			else if (indicator == "CREDIT:")
			{
				credit = line.erase(0,8);
				add_user->setCreditCardInfo(credit);			}
			// set user's movie rental
			else if (indicator == "MOVIE:")
			{
				getline(ss, buffer, ' ');
				getline(ss, movie_title);
				Movie* movie_rental;
				movie_rental = new Movie(movie_title);
				add_user->rentMovie(movie_rental);

			}
			else if (indicator == "END")
			{
					// add new user to map
					user_map.add(user_id, add_user);
			}
			else 
			{
				break;
			}

		}
	}

	ifile.close();
}

//  open and parse movie file 
void Netflix::read_movie_file (string movie_file)
{

	ifstream ifile;
	ifile.open(movie_file.c_str());

	if (ifile.fail())
	{
		cerr << "\t\nError. Invalid Movie File. Please try again." << endl;
		exit(0);
	}	
	else
	{
		string line = "";
		string indicator = "";
		string movie_title = "";
		string keyword = "";
		string general_title = "";
		string general_keyword = "";
		string actor_name = "";
		string general_actor = "";

		while (getline(ifile,line))
		{
			stringstream ss(line);
			ss >> indicator; 

			if (indicator == "BEGIN")
			{
				movie_title = line.erase(0,6);

				//add new movie to map 
				Movie* add_movie;
				add_movie = new Movie(movie_title);
				general_title = movie_title;
				// change to all lowercase in order to find later
				transform(general_title.begin(), general_title.end(), general_title.begin(), ::tolower);
				movie_map.add(general_title, add_movie);


			}
			else if (indicator == "KEYWORD:")
			{
				keyword = line.erase(0,9);

				//add to keyword map for lookup
				// change to all lowercase for lookup
				general_keyword = keyword;
				transform(general_keyword.begin(), general_keyword.end(), general_keyword.begin(), ::tolower);
				movie_map.get(general_title)->addKeyword(keyword);
				//check if keyword is in map
				if (keyword_lookup_map.contains(general_keyword))
				{
					keyword_lookup_map.get(general_keyword)->add(movie_map.get(general_title));
				}
				else
				{
					// list of movies in set in order to store all info
					Set<Movie*>* new_movie = new Set<Movie*>;
					new_movie->add(movie_map.get(general_title));
					keyword_lookup_map.add(general_keyword, new_movie);
				}

			}
			else if (indicator == "ACTOR:")
			{
				actor_name = line.erase(0,7);

				//add to keyword map for lookup
				// change to all lowercase for lookup
				general_actor = actor_name;
				transform(general_actor.begin(), general_actor.end(), general_actor.begin(), ::tolower);
				movie_map.get(general_title)->addKeyword(actor_name);
				//check if keyword is in map
				if (keyword_lookup_map.contains(general_actor))
				{
					keyword_lookup_map.get(general_actor)->add(movie_map.get(general_title));
				}
				else
				{
					// list of movies in set in order to store all info
					Set<Movie*>* new_movie = new Set<Movie*>;
					movie_map.get(general_title)->addActor(actor_name);
					new_movie->add(movie_map.get(general_title));
					keyword_lookup_map.add(general_actor, new_movie);
				}

			}
			else if (indicator == "END")
			{

			}
			else 
			{
				break;
			}

		}

	}

	ifile.close();
}

void Netflix::first_menu_text()
{
	cout << "\nPlease select one of the following options:" << endl;
	cout << "1. Log In" << endl;
	cout << "2. Create a new user" << endl;
	cout << "3. Quit" << endl;
}

void Netflix::logged_in_menu_text()
{
	cout << "\nPlease select one of the following options:" << endl;
	cout << "1. Search for a movie by title" << endl;
	cout << "2. Search for a movie by keyword" << endl;
	cout << "3. Return the current movie" << endl;
	cout << "4. View queue" << endl;
	cout << "5. Logout" << endl;
}

void Netflix::penultimate_menu ()
{
	cout << "\n1. Next movie" << endl;
	cout << "2. Add movie to queue" << endl;
	cout << "3. Return to menu" << endl;
}

void Netflix::view_queue_menu_text ()
{
	cout << "\n1. Order movie" << endl;
	cout << "2. Remove from queue" << endl;
	cout << "3. Move current movie to back of queue" << endl;
	cout << "4. Return to user menu" << endl;
}

void Netflix::final_menu ()
{

	cout << "\n1. Add movie to queue" << endl;
	cout << "2. Return to menu" << endl;

}

void Netflix::last_menu ()
{
	cout << "\n1. Return to menu" << endl;
}

// allow user to select options of log in, create new user, quit
void Netflix::first_menu()
{
	while(true)
	{
		string entry = "";
		int entry_number = 0;
		first_menu_text();

		getline(cin, entry);
		while (cin.fail ())
		{

			cout << "\t\nInvalid user entry. Please try again." << endl;
			getline(cin,entry);

		}

		stringstream ss;
		ss << entry;
		ss >> entry_number;

		while(entry_number != 1 && entry_number != 2 && entry_number != 3)
		{
			cout << "\t\nInvalid input. Please try again." << endl;
			first_menu_text();
			getline(cin, entry);
			if (cin.fail ())
			{

				cout << "\t\nInvalid user entry. Please try again." << endl;

			}

			stringstream iss;
			iss << entry;
			iss >> entry_number;
		}


		string user_id_entry = "";

		if(entry_number == 1)
		{
			// cout << "\nEnter your specific Login ID:" << endl;
			// getline(cin, user_id_entry);
			// while (cin.fail ())
			// {

			// cout << "\t\nInvalid user entry. Please try again." << endl;
			// getline(cin,entry);

			// }
			
			// if (user_map.contains(user_id_entry))
			// {

			// 	logged_in_menu(user_id_entry);

			// }

			// else
			// {
			// 	cout << "\nUser not found." << endl;

			// }

		}
		else if(entry_number == 2)
		{
			cout << "\nPlease enter your desired ID:" << endl;
			
			getline(cin, user_id_entry);
			while (cin.fail ())
			{

			cout << "\t\nInvalid user entry. Please try again." << endl;
			getline(cin,entry);

			}

			while(user_map.contains(user_id_entry))
			{

				cout << "\nID unavailable." << endl;
				cout << "Please enter your desired ID:" << endl;
				getline(cin, user_id_entry);
				if (cin.fail ())
				{

					cout << "\t\nInvalid user entry. Please try again." << endl;

				}

			}

			string nombre = "";
			cout << "\nPlease enter your name:" << endl;
			getline(cin, nombre);
			while (cin.fail ())
			{

				cout << "\t\nInvalid user entry. Please try again." << endl;
				getline(cin,entry);

			}

			User* add_user = new User(user_id_entry, nombre);
			user_map.add(user_id_entry, add_user);

			logged_in_menu(user_id_entry);



		}
		// update user file before finally quitting program
		else if(entry_number == 3)
		{
			update_user_file();
			exit(0);
		}
		
	}

}

// allow user to search or quit
void Netflix::logged_in_menu(string user_id)
{
	while(true)
	{
		string entry = "";
		int entry_number;
		logged_in_menu_text();

		getline(cin, entry);
		while (cin.fail ())
		{

			cout << "\t\nInvalid user entry. Please try again." << endl;
			getline(cin,entry);

		}

		stringstream ss;
		ss << entry;
		ss >> entry_number;

		while(entry_number < 1 || entry_number > 5)
		{
			cout << "\t\nInvalid input. Please try again." << endl;
			logged_in_menu_text();
			getline(cin, entry);
			while (cin.fail ())
			{

				cout << "\t\nInvalid user entry. Please try again." << endl;
				getline(cin,entry);

			}

			stringstream iss;
			iss << entry;
			iss >> entry_number;
		}

		// search if movie exists in map
		if(entry_number == 1)
		{
			cout << "\nPlease enter the name of the movie:" << endl;
			
			string movie;
			getline(cin, movie);
			while (cin.fail ())
			{

				cout << "\t\nInvalid user entry. Please try again." << endl;
				getline(cin,entry);

			}

			transform(movie.begin(), movie.end(), movie.begin(), ::tolower);

			// check if movie is in map
			if (!movie_map.contains(movie))
			{

				cerr << "\nMovie not found." << endl;

			}
			else
			{
				// print keywords
				cout << movie_map.get(movie)->getTitle() << endl;
				movie_map.get(movie)->getAllKeywords().printKeyOnly();
			}

		}
	
		// keyword search
		else if(entry_number == 2)
		{

			cout << "\nPlease enter (a) keyword(s):" << endl;
			string user_keyword = "";
			getline(cin, user_keyword);
			while (cin.fail ())
			{

				cout << "\t\nInvalid user entry. Please try again." << endl;
				getline(cin,entry);

			}

			transform(user_keyword.begin(), user_keyword.end(), user_keyword.begin(), ::tolower);
			if (!keyword_lookup_map.contains(user_keyword)) // check if keyword exists in map
			{

				cerr << "\nKeyword(s) not found." << endl;

			}

			else 
			{
				// print first movie title for movies matching keywords
				int keyword_map_size = keyword_lookup_map.get(user_keyword)->size();
				Set<Movie*>* temp_set = keyword_lookup_map.get(user_keyword);
				Set<Movie*>::Iterator movie_it = temp_set->begin();
				int buffer = 1;

				cout << endl;
				cout << (*movie_it)->getTitle() << endl;

				while (buffer < keyword_map_size)
				{

					penultimate_menu();
					getline(cin, entry);
					while (cin.fail ())
					{

						cout << "\t\nInvalid user entry. Please try again." << endl;
						getline(cin,entry);

					}

					stringstream iss;
					iss << entry;
					iss >> entry_number;

					// iterate through movies matching keyword
					if (entry_number == 1)
					{

						++movie_it;
						cout << endl;
						cout << (*movie_it)->getTitle() << endl;

						// keyword_lookup_map.get(user_keyword)->next();
						// cout << keyword_lookup_map.get(user_keyword)->getCurrent()->getTitle() << endl;
						buffer++;

					}

					// add to user's movie queue
					else if (entry_number == 2)
					{
						cout << "\nAdding " << (*movie_it)->getTitle() << " to your queue." << endl;
						user_map.get(user_id)->movieQueue()->enqueue(*movie_it);
					}

					// return to user menu
					else if (entry_number == 3)
					{
						logged_in_menu(user_id);
					}

					else 
					{

						while (entry_number!=1 && entry_number!=2)
						{
							penultimate_menu();
							getline(cin, entry);
							while (cin.fail ())
							{

								cout << "\t\nInvalid user entry. Please try again." << endl;
								getline(cin,entry);

							}

							stringstream iss;
							iss << entry;
							iss >> entry_number;
						}
					}

				}

				// only one movie left that matches keyword
				if (buffer >= keyword_map_size)
				{

					final_menu();
					getline(cin, entry);
					while (cin.fail ())
					{

						cout << "\t\nInvalid user entry. Please try again." << endl;
						getline(cin,entry);

					}
			
					stringstream iss;
					iss << entry;
					iss >> entry_number;

					while (entry_number!=1 && entry_number != 2)
					{
						final_menu();
						getline(cin, entry);
						while (cin.fail ())
						{
		
							cout << "\t\nInvalid user entry. Please try again." << endl;
							getline(cin,entry);

						}

						stringstream iss;
						iss << entry;
						iss >> entry_number;
					}

					if (entry_number == 1) // add movie to user queue
					{
						cout << "\nAdding " << (*movie_it)->getTitle() << " to your queue." << endl;
						user_map.get(user_id)->movieQueue()->enqueue(*movie_it);
						last_menu();
						getline(cin, entry);
						while (cin.fail ())
						{

							cout << "\t\nInvalid user entry. Please try again." << endl;
							getline(cin,entry);

						}
				
						stringstream iss;
						iss << entry;
						iss >> entry_number;

						while (entry_number!=1)
						{
							last_menu();
							getline(cin, entry);
							while (cin.fail ())
							{
			
								cout << "\t\nInvalid user entry. Please try again." << endl;
								getline(cin,entry);

							}

							stringstream iss;
							iss << entry;
							iss >> entry_number;
						}

						logged_in_menu(user_id);

					}

					// return to user menu
					else if (entry_number == 2)
					{
						logged_in_menu(user_id);
					}

				}
			}

		}

		// return user movie rental
		else if (entry_number == 3)
		{
			if (user_map.get(user_id)->currentMovie() == NULL)
			{
				cout << "\nYou do not have a rented movie at this time." << endl;
			}
			else 
			{
				cout << "\nYour rental " << user_map.get(user_id)->currentMovie()->getTitle() << " has been returned." << endl;
				user_map.get(user_id)->returnMovie();
			}
		}

		// view user queue
		else if (entry_number == 4)
		{
			if (user_map.get(user_id)->movieQueue()->isEmpty())
			{
				cout << "\nMovie queue empty" << endl;
			}

			else
			{

				cout << "\nMovies in your queue: " <<user_map.get(user_id)->movieQueue()->peekFront()->getTitle() << endl;

				view_queue_menu_text ();
				getline(cin, entry);
				while (cin.fail ())
				{
					cout << "\t\nInvalid user entry. Please try again." << endl;
					getline(cin,entry);
				}
				
				stringstream iss;
				iss << entry;
				iss >> entry_number;

				while (entry_number!=1 && entry_number!=2 && entry_number != 3 && entry_number != 4)
				{
					view_queue_menu_text();
					getline(cin, entry);
					while (cin.fail ())
					{
						cout << "\t\nInvalid user entry. Please try again." << endl;
						getline(cin,entry);
					}

					stringstream iss;
					iss << entry;
					iss >> entry_number;
				}

				// order movie
				if (entry_number == 1)
				{
					if (user_map.get(user_id)->currentMovie() == NULL)
					{
						cout << "\nOrder: " << user_map.get(user_id)->movieQueue()->peekFront()->getTitle() << " complete." << endl;
						user_map.get(user_id)->rentMovie(user_map.get(user_id)->movieQueue()->peekFront());
						user_map.get(user_id)->movieQueue()->dequeue();
					}
					else
					{
						cout << "\nCannot order movie because ";
						cout << user_map.get(user_id)->currentMovie()->getTitle() << " is currently checked out." << endl;
						cout << "Please return the movie before ordering another one." << endl;
					}
				}

				// remove first movie from queue
				else if (entry_number == 2)
				{
					cout << "\nRemoving " << user_map.get(user_id)->movieQueue()->peekFront()->getTitle() << " from queue" << endl;
					user_map.get(user_id)->movieQueue()->dequeue();
				}

				// move first movie to back of queue
				else if (entry_number == 3)
				{
					cout << "\nMoving " << user_map.get(user_id)->movieQueue()->peekFront()->getTitle() << " to back of queue." << endl;
					Movie* replace_movie;
					replace_movie = user_map.get(user_id)->movieQueue()->peekFront();
					//replace_movie = user_map.get(user_id)->movieQueue()->peekFront();
					user_map.get(user_id)->movieQueue()->dequeue();
					user_map.get(user_id)->movieQueue()->enqueue(replace_movie);
				}

				// return to user menu 
				else if (entry_number == 4)
				{
					logged_in_menu(user_id);
				}

			}
		}

		// return to log in menu
		else if(entry_number == 5)
		{
			first_menu();
		}
	}
}

User* Netflix::getUser(string user_ID)
{
	// Map<string, User*>::Iterator uit = user_map.begin();
		Map<string, User*>::Iterator uit = user_map.begin();

		User* temp_user = (*uit).second;

	// iterator through user map
	for (uit; uit != user_map.end(); ++uit)
	{
		//User* temp_user = (*uit).second;
		temp_user = (*uit).second;

		if (temp_user->getID() == user_ID)
		{
			return temp_user;
		}
	}

	return NULL;

}

Movie* Netflix::getMovie(string movie_title)
{
	Map<string, Movie*>::Iterator mit;

	for (mit = movie_map.begin(); mit != movie_map.end(); ++mit)
	{
		Movie* temp_movie = (*mit).second;
		string temp_title = temp_movie->getTitle();
		transform(temp_title.begin(), temp_title.end(), temp_title.begin(), ::tolower);

		if (temp_title == movie_title)
		{
			return temp_movie;
		}
	}

	return NULL;
}

// overwrite current user file
void Netflix::update_user_file()
{

	ofstream ofile; 
	ofile.open(user_file.c_str());

	Map<string, User*>::Iterator uit = user_map.begin();

	// iterator through user map
	for (uit; uit != user_map.end(); ++uit)
	{
		User* temp_user = (*uit).second;

		string begin = "BEGIN ";
		string name = "NAME: ";
		string password = "PASSWORD: ";
		string address = "ADDRESS: ";
		string credit = "CREDIT: ";
		string movie = "MOVIE: ";
		string end = "END";
		ofile << begin.append(temp_user->getID()) << endl;
		ofile << name.append(temp_user->getName()) << endl;
		ofile << password.append(temp_user->getHash()) << endl;
		ofile << address.append(temp_user->getAddress()) << endl;
		ofile << credit.append(temp_user->getCreditHash()) << endl;
		if (temp_user->currentMovie() != NULL) /// check if user has movie rented or not to print user's movie rental
		{
			ofile << movie.append(temp_user->currentMovie()->getTitle()) << endl;
		}
		if (!temp_user->movieQueue()->isEmpty()) // check if user has movies in queue to print movies in queue
		{

			begin = "BEGIN ";
			ofile << begin + "QUEUE" << endl;
			// print all queue contents
			for (int i = 0; i < temp_user->movieQueue()->size(); i++)
			{
				ofile << temp_user->movieQueue()->peekFront()->getTitle() << endl;
				Movie* replace_movie;
				replace_movie = user_map.get(temp_user->getID())->movieQueue()->peekFront();
				user_map.get(temp_user->getID())->movieQueue()->dequeue();
				user_map.get(temp_user->getID())->movieQueue()->enqueue(replace_movie);
			}

			ofile << end + " QUEUE" << endl;
		}
		if (temp_user->rating_map()->size() > 0)
		{
			begin = "BEGIN ";
			ofile << begin + "RATINGS" << endl;
			Map<string, int>::Iterator mit = temp_user->rating_map()->begin();
			// cout << "size " << temp_user->rating_map()->size() << endl;
			
			for (mit; mit != temp_user->rating_map()->end(); ++mit)
			{
				string movie_buffer = (*mit).first;
				int movie_rating = (*mit).second;
				// cout << movie_buffer->getTitle() << endl;
				ofile << movie_rating; 
				ofile << " " + movie_buffer << endl;
			}
			ofile << end + " RATINGS" << endl;
		}

		ofile << end << endl;
	}

	ofile.close();

}
