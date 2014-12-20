#ifndef SET_H
#define SET_H

#include "DLL.h"
// #include "Movie.h"
#include <string>
#include <iostream>
#include "Mergesort.h"
#include <vector>

using namespace std;

template <class T>
class Set
{
  public:

    class Iterator {
         /* add any constructors that you feel will be helpful,
            and choose whether to make them public or private. */

        public:

            friend class Set<T>;
            
            T operator* () const
            {
                Pair<T,T> temp_pair = *it;
                return temp_pair.first;
            }


           Set<T>::Iterator operator++ ()
           {
                ++it;
                return *this;
           }

           Set<T>::Iterator operator= (const Set<T>::Iterator & other)
           {
                if(this != &other)
                {
                    it = other.it;
                }
                return *this;
           }
              // assigns the other iterator to this iterator and returns this

           bool operator== (const Set<T>::Iterator & other) const
           {
                return (it == other.it);
           }
              // returns whether this iterator is equal to the other iterator

           bool operator!= (const Set<T>::Iterator & other) const
           {
               return (!this->operator== (other));
           }

           Iterator ()
           {
                whoIBelongTo = NULL;
                //it = NULL;
           }

            // Iterator(const Set<T> *s, typename Map<T,T>::Iterator *m)
            // {
            //     whoIBelongTo = s;
            //     it = m;
            // }
            Iterator(const Set<T> *s, bool begin)
            {
                whoIBelongTo = s;
                if (begin)
                {
                    it = whoIBelongTo->internalStorage.begin();
                }
                else
                {
                    it = whoIBelongTo->internalStorage.end();
                }
            }
              // returns whether this iterator is not equal to the other iterator

           /* Optionally, if you think that it makes your code easier to write,
              you may also overload other operators: */

           /* You may define a public copy constructor and/or default constructor
              if you think it would be helpful. */

        private: 

            const Set<T> *whoIBelongTo;
            typename Map<T,T>::Iterator it;

     };

    Set<T>::Iterator begin () const
    {   
        // Set<T>::Iterator *sit;
        // sit = new Set<T>::Iterator(this, &(internalStorage.begin()));
        // return *sit; 
        return *(new Set<T>::Iterator(this, true));
    }
       // returns an iterator initialized to the first element

    Set<T>::Iterator end () const
    {
        //Set<T>::Iterator *sit;
        return *(new Set<T>::Iterator(this, false));
        //return *sit;
    }
       /* returns an iterator initialized past the last element,
          to designate that the end of the map has been reached. */


    Set ();  // constructor for a new empty set

    Set (const Set<T> &other); // Deep Copy Constructor 

    ~Set (); // destructor

    Set & operator = (const Set<T> &other);

    int size () const; // returns the number of elements in the set

    void add (const T &item); 
      /* Adds the item to the set.
         If the item is already in the set, it should do nothing.
      */

    void remove (const T &item);
     /* Removes the item from the set.
        If the item was not in the set, it should do nothing. */

    bool contains (T item) const;
     /* Returns whether the item is in the set. */

    void merge (const Set<T> & other);
     /* Adds all elements of other to this set. 
        However, will not create duplicates, i.e., it ignores elements
        already in the set. */

    // void first (); // set to first node

    // void next (); // move to next node

    // const T & getCurrent (); // reeturn current node

    Set<T> setUnion (const Set<T> & other) const; // combine all set elements

    Set<T> setIntersection (const Set<T> & other) const; // return only common set elements

    string printKeyOnly () const; // print key from list only

  private:
    Map<T, T> internalStorage;
    int counter;
     /* You should use a Map (your own implementation) to store your set.
        It is part of your assignment to figure out what types you 
        need for the keyType and valueType. */

     /* If you like, you can add further data fields and private
        helper methods. */
};

template <class T>
Set<T>::Set ()
{
    
    counter = 0;

}

template <class T>
Set<T>::Set (const Set<T> &other)
{

    internalStorage.merge(other.internalStorage);

}

template <class T>
Set<T> & Set<T>::operator = (const Set<T> &other)
{
    this->internalStorage = other.internalStorage;
    return *this;
}

template <class T>
Set<T>::~Set ()
{

}

template <class T>
int Set<T>::size () const
{
    // return counter/size 
    return this->internalStorage.size ();

}


// template <class T>
// void Set<T>::first ()
// {

//     internalStorage.first();

// }

// template <class T>
// void Set<T>::next ()
// {

//     internalStorage.next();

// }

template <class T>
void Set<T>::add (const T &item)
{
    // add from set 
    if (!contains(item))
    {
        internalStorage.add(item, item);
        counter++;
    }

}

template <class T>
void Set<T>::remove (const T &item)
{
    // remove from set 
   if (contains(item))
   {
       internalStorage.remove(item);
       counter--;
   }

}

template <class T>
bool Set<T>::contains (T item) const 
{

    bool success = false; 
    try
    {

        internalStorage.get(item);
        success = true;

    }

    catch(...)
    {

        return success;

    }

    return success;

}

template <class T>
void Set<T>::merge (const Set<T> & other)
{

    // merge sets using map 
    internalStorage.merge(other.internalStorage);
    // other.is is a map itself 
    
}

// template <class T>
// const T & Set<T>::getCurrent ()
// {

//   return internalStorage.getCurrentKey();

// }

// merge this and other into one set with all elements 
template <class T>
Set<T> Set<T>::setUnion (const Set<T> & other) const // FIX THIS INSTANTIATION ISSUE
{

  vector<T> v1, v2;
  Set<T>::Iterator sit1 = this->begin();
  Set<T>::Iterator sit2 = other->begin();

  while (sit1 != this->end())
  {
    v1.push_back(*sit1);
    ++sit1;
  }
  while (sit2 != other->end())
  {
    v2.push_back(*sit2);
    ++sit2;
  }

  vector<T> v1sort = MergeSort::sort(v1);
  vector<T> v2sort = MergeSort::sort(v2);

  int v1c = 0;
  int v2c = 0;

  vector<T> final_vector;

  while (v1c < v1sort.size() && v2c < v2sort.size())
  {
    if (v1sort.at(v1c) < v2sort.at(v2c))
    {
      final_vector.push_back(v1sort.at(v1c));
      v1c++;
    }
    else if (v1sort.at(v1c) > v2sort.at(v2c))
    {
      final_vector.push_back(v2sort.at(v2c));
      v2c++;
    }
    else if (v1sort.at(v1c) == v2sort.at(v2c))
    {
      final_vector.push_back(v1sort.at(v1c));
      v1c++;
      v2c++;
    }
  }

  if (v1c < v1sort.size())
  {
    int counter = 0;
    while (counter != v1sort.size()-1)
    {
      final_vector.push_back(v1sort.at(counter));
      counter++;
    }
  }

  if (v2c < v2sort.size())
  {
    int counter = 0;
    while (counter != v2sort.size()-1)
    {
      final_vector.push_back(v2sort.at(counter));
      counter++;
    }
  }

  Set<T> final_set;
  int count = 0;
  while (counter != final_vector.size()-1)
  {
    final_set.add(final_vector.at(count));
  }

  return final_set;
}

// combine into new set common elements 
template <class T>
Set<T> Set<T>::setIntersection (const Set<T> & other) const
{

  vector<T> v1, v2;
  Set<T>::Iterator sit1 = this->begin();
  Set<T>::Iterator sit2 = other->begin();

  while (sit1 != this->end())
  {
    v1.push_back(*sit1);
    ++sit1;
  }
  while (sit2 != other->end())
  {
    v2.push_back(*sit2);
    ++sit2;
  }

  vector<T> v1sort = MergeSort::sort(v1);
  vector<T> v2sort = MergeSort::sort(v2);

  int v1c = 0;
  int v2c = 0;

  vector<T> final_vector;

  while (v1c < v1sort.size() && v2c < v2sort.size())
  {
    if (v1sort.at(v1c) < v2sort.at(v2c))
    {
      v1c++;
    }
    else if (v1sort.at(v1c) > v2sort.at(v2c))
    {
      v2c++;
    }
    else if (v1sort.at(v1c) == v2sort.at(v2c))
    {
      final_vector.push_back(v1sort.at(v1c));
      v1c++;
      v2c++;
    }
  }

  Set<T> final_set;
  int count = 0;
  while (counter != final_vector.size()-1)
  {
    final_set.add(final_vector.at(count));
  }

  return final_set;

}

template <class T> 
string Set<T>::printKeyOnly () const
{
    return this->internalStorage.printKeyOnly();
}

// #include "User.h"
// #include "Movie.h"

#endif