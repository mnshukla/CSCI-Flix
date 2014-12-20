#include <iostream>
#include <string>
#include "Movie.h"

using namespace std;

Movie::Movie (string title)
{
	movie_title = title;
}

Movie::Movie(const Movie & other)
{
	movie_title = other.movie_title;
	keyword_set = other.keyword_set;
}

Movie::~Movie()
{


}

string Movie::getTitle () const
{
	return movie_title;
}

void Movie::addKeyword (string keyword)
{
	
	if(!keyword_set.contains(keyword))
	{
		keyword_set.add(keyword);
	}
}

 Set<string> Movie::getAllKeywords () const
 {
 	Set<string> foo_set (keyword_set);
 	return foo_set;
 }

 void Movie::addActor(string actor_name)
 {
 	actor_set.add(actor_name);
 }