#ifndef USER_H
#define USER_H

#include "Set.h"
#include "Queue.h"
#include "Movie.h"
#include <string>

class User {
  public:
    User (string ID, string name);  
    /* constructor that generates a user with the given name and ID.
       While multiple users may have the same name, the ID should be unique
       (e.g., an e-mail address), so that users can log in with it. */

    User (const User & other); // copy constructor

    ~User ();            // destructor

    string getID () const;    // returns the ID associated with this user

    string getName () const;  // returns the name associated with this user

    Queue<Movie*> * movieQueue (); 
      /* returns a pointer to the user's movie queue.
         This is the easiest way to ensure that you can modify the queue.
         (If you return by reference, that's also possible, but you'd need
         to be very careful not to invoke any deep copy constructors or
         assignments. A pointer is thus safer.) */

    void rentMovie (Movie *m);
      /* sets the user's currently rented movie to m.
         If the user already has a movie checked out, then it does nothing.
         (So no overwriting the current movie.) */

    void returnMovie ();
      /* returns the movie that the user currently has checked out.
         Does nothing if the user doesn't currently have a movie. */

    void addCharge ();

    void setAddress (string _address);

    void setCreditCardInfo (string _credit_card_info);

    void setPassword (string _password);

    string getHash() const;

    string getCharges () const;

    string getAddress () const;

    string getCreditHash() const;

    Movie* currentMovie () const;
      /* returns the user's current checked out movie.
         Returns NULL if the user has no movie checked out. */

    Map<string, int> * rating_map ();

  private:
    // you get to decide what goes here.
    string user_id;
    string user_name;
    Queue<Movie*> *user_movie_queue; 
    int number_of_movies;
    Movie* rented_movie;
    Map<string, int> *user_ratings_map;
    string password;
    string address;
    string credit_card_info;
    int total_charges;

};

#endif 