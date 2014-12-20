#ifndef DLL_H
#define DLL_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <class keyType, class valueType>
struct MapItem
{
  keyType key;
  valueType value;
  MapItem<keyType, valueType> *prev, *next;
};

class NoSuchElementException
{

};

template <class FirstType, class SecondType> 
struct Pair {
  FirstType first;
  SecondType second;

  Pair (FirstType first, SecondType second)
  { 
    this->first = first; 
    this->second = second; 
  }
};

template <class keyType, class valueType>
class Map
{
  public:

    class Iterator 
    {
         /* add any constructors that you feel will be helpful,
            and choose whether to make them public or private. */

      public:

        Pair<keyType, valueType> operator* () const
        {
          Pair<keyType, valueType> temp_pair(currentMapItem->key,currentMapItem->value);
          return temp_pair;
        }
              // return the current (key, value) pair the iterator is at

        Map<keyType,valueType>::Iterator operator++ ()
        {
          currentMapItem = currentMapItem->next;
          return *this;
        }
              // advances the iterator (pre-increment)

        Map<keyType,valueType>::Iterator operator= (const Map<keyType,valueType>::Iterator & other)
        {
          if(this != &other)
          {
            whoIBelongTo = other.whoIBelongTo;
            currentMapItem = other.currentMapItem;
          }
          return *this;
        }
              // assigns the other iterator to this iterator and returns this

        bool operator== (const Map<keyType,valueType>::Iterator & other) const
        {
          return (currentMapItem == other.currentMapItem && whoIBelongTo == other.whoIBelongTo);
        }
              // returns whether this iterator is equal to the other iterator

        bool operator!= (const Map<keyType,valueType>::Iterator & other) const
        {
           return (!this->operator== (other));
        }
              // returns whether this iterator is not equal to the other iterator

           /* Optionally, if you think that it makes your code easier to write,
              you may also overload other operators: */

           /* You may define a public copy constructor and/or default constructor
              if you think it would be helpful. */

        friend class Map<keyType, valueType>;

        Iterator ()
        {
          whoIBelongTo = NULL;
          currentMapItem = NULL;
        }

         Iterator(const Map<keyType, valueType> *m, MapItem<keyType, valueType> *p)
        {
          whoIBelongTo = m;
          currentMapItem = p;

        }

      private:

        const Map<keyType, valueType> *whoIBelongTo;

        MapItem<keyType, valueType> *currentMapItem;


    };

    typename Map<keyType,valueType>::Iterator begin () const
    {
       return *(new Map<keyType, valueType>::Iterator(this, head));
    }
       // returns an iterator initialized to the first element

    typename Map<keyType,valueType>::Iterator end () const
    {
      return *(new Map<keyType, valueType>::Iterator(this, NULL));
    }
       /* returns an iterator initialized past the last element,
          to designate that the end of the map has been reached. */

    Map ();  // constructor for a new empty map

    Map (const Map<keyType, valueType> &other); // Deep Copy Constructor

    Map<keyType, valueType> & operator = (const Map<keyType, valueType> &other); // Overloaded Assignment Operator 

    ~Map (); // destructor

    int size () const; // returns the number of key-value pairs

    void add (const keyType &key, const valueType &value); 
      /* Adds a new association between the given key and the given value.
         If the key already has an association, it should do nothing.
      */

    void remove (const keyType &key);
     /* Removes the association for the given key.
        If the key has no association, it should do nothing. */

    const valueType & get (const keyType & key) const;
     /* Returns the value associated with the given key.
        If the key existed in the map, success should be set to true.
        If the key has no association, it should set success to false. */

    void merge (const Map<keyType, valueType> & other);
     /* Adds all the key-value associations of other to the current map.
        If both maps (this and other) contain an association for the same
        key, then the one of this is used. */

    // void first (); // resets to first node

    // void next (); // moves to next node

    bool contains(keyType key) const; // find out if key is in  map

    // const keyType & getCurrentKey (); // returns current node's key

    // const valueType & getCurrentValue (); // returns current node's value

    MapItem<keyType, valueType>* find_key(keyType key) const; // returns pointer to node

    MapItem<keyType, valueType>* get_node_at_index(int) const; // finds current node returns current node

    string printKeyOnly () const; // print's node key

  private:
     /* The head and tail of the linked list you're using to store
        all the associations. */

     // MapItem<keyType, valueType>* get_node_at_index(int) const;

     MapItem <keyType, valueType> *head, *tail, *currentNode;
     int counter;

     /* If you like, you can add further data fields and private
        helper methods. */
};


template<class keyType, class valueType>
Map<keyType, valueType>::Map () 
{

  counter = 0; // set initial size of list to 0
  head = NULL;
  tail = NULL;

}

template<class keyType, class valueType>
Map<keyType, valueType>::Map (const Map<keyType, valueType> &other) // Deep Copy Constructor
{

  head = new MapItem<keyType, valueType>;
  tail = new MapItem<keyType, valueType>;

  head = other.head; 
  MapItem<keyType,valueType>* temp = new MapItem<keyType, valueType>(); 
  MapItem<keyType,valueType>* otherTemp = new MapItem<keyType, valueType>(); 

  temp = head;
  otherTemp = other.head;
  for (int i = 0; i < counter; i++) 
  {

    if (otherTemp->next != NULL)
    {

      temp->key = otherTemp->key;
      temp->value = otherTemp->value; 
      temp->next = otherTemp->next;
      temp->prev = otherTemp->prev;

    }

    else 
    {

    }

  }
  tail = other.tail; 
  tail->next = NULL;
  counter = other.counter;

}

template<class keyType, class valueType>
Map<keyType, valueType> & Map<keyType, valueType>::operator = (const Map<keyType, valueType> &other) 
{

  if(this == &other)
  {
    return *this;
  }
  else
  {

    while(this->head)
    {

      this->remove(this->get_node_at_index(0)->key);

    }

    for(int k = 0; k < other.size(); k++)
    {

      this->add(other.get_node_at_index(k)->key, other.get_node_at_index(k)->value);

    }

    return *this;

  }

}

template<class keyType, class valueType>
Map<keyType, valueType>::~Map () 
{

  while (head != NULL)
  {

    remove(get_node_at_index(0)->key);

  }

}

template<class keyType, class valueType> 
int Map<keyType, valueType>::size () const
{

  return counter; // return size 

}

// check to see if key is in linked list
template<class keyType, class valueType> 
MapItem<keyType, valueType>* Map<keyType, valueType>::find_key(keyType key) const
{

  MapItem<keyType, valueType>* head_temp;

  head_temp = head; // set temp to start of list

  // traverse list 
  while (head_temp != NULL)
  {

    if (head_temp->key == key)
    {
      return head_temp; // return pointer to mapitem so it can be directly referenced to inside other functions 
    }

    else
    {
      head_temp = head_temp->next;

    }

  }

  return NULL;

}

// // go to start of list
// template<class keyType, class valueType> 
// void Map<keyType, valueType>::first ()
// {

//   if (head != NULL)
//   {

//   currentNode = head; // set temp to start of list
//   return;
//   }

//   NoSuchElementException expectionToThrow;
//   throw expectionToThrow;
// }

// // move to next node
// template<class keyType, class valueType> 
// void Map<keyType, valueType>::next ()
// {

//   // traverse list 
//   if (currentNode->next != NULL)
//   {

//       currentNode = currentNode->next;
//       return;

//   }

//   NoSuchElementException expectionToThrow;
//   throw expectionToThrow;

// } 

// check if key is in list
template<class keyType , class valueType > 
bool Map<keyType, valueType>::contains(keyType key) const
{

  bool success = false;

  for (int i = 0; i < counter; i++)
  {

    if (key == get_node_at_index(i)->key)
    {

      success = true;
      return success;

    }

  }

  return success;

}

// remove item from list 
template<class keyType , class valueType > 
void Map<keyType, valueType>::remove(const keyType &key)
{

  MapItem<keyType, valueType>* map_temp;
  map_temp = find_key(key); // check to see if item is in map 

  if (map_temp == NULL)
  {

    return; // not in list 

  }


  if(map_temp == head)
  {

    if (counter == 1) 
    {

      head = NULL; // only 1 item in list

    }

    else 
    {

      head = map_temp->next;
      map_temp->next->prev = NULL; // remove head 

    }

  }
  
  else if (map_temp == tail)
  {

    if (counter == 1) // only 1 item in list 
    {

      tail = NULL;

    }

    else 
    {

    map_temp->prev->next = NULL;
    tail = map_temp->prev;

    } 

  }
  else // item in middle of list 
  {
  
    map_temp->prev->next = map_temp->next;
    map_temp->next->prev = map_temp->prev; 
  
  }

  
  delete map_temp;
  
  counter--; // decrement size 
  
}


template<class keyType, class valueType > 
void Map<keyType, valueType>::add(const keyType &key, const valueType &value)
{

  MapItem<keyType, valueType>* map_temp;
  map_temp = find_key(key);

  if (map_temp == NULL) // key not in list 
  {
    if (head == NULL) // not items in list 
    { 

      MapItem<keyType, valueType>* item = new MapItem<keyType, valueType> ();

      
      head = item;
      tail = item;
      
      item->key = key;
      item->value = value;
      item->next = NULL;
      item->prev = NULL;

      counter++;
      
    }

    else // add item to end of list 
    {

      MapItem<keyType, valueType>* item = new MapItem<keyType, valueType> ();

      item->prev = tail;
      item->next = NULL;

      tail->next = item;

      tail = item;

      item->key = key;
      item->value = value;

      counter++;
    }

  }

  else
  {
  
  }

}

// return value of key and make sure that the key was in list 
template<class keyType, class valueType> 
const valueType& Map<keyType, valueType>::get(const keyType & key) const
{

  MapItem<keyType, valueType>* map_temp;
  map_temp = find_key(key);
  if (map_temp != NULL) // key in list and value returned 
  {

    return map_temp->value; 

  }

  else // key not in list
  {

    NoSuchElementException expectionToThrow;
    throw expectionToThrow;

  }

}

// traverse through list and returning each node one at a time
template <class keyType, class valueType>
MapItem<keyType, valueType>* Map<keyType, valueType>::get_node_at_index (int num) const
{

  MapItem<keyType, valueType>* head_temp;
  head_temp = head;

  for (int i = 0; i < num; i++)
  {

    head_temp = head_temp->next; 


  }

  return head_temp;

}

// // return current key
// template <class keyType, class valueType>
// const keyType& Map<keyType, valueType>::getCurrentKey ()
// {

//   return currentNode->key;

// }

// // return current value 
// template <class keyType, class valueType>
// const valueType& Map<keyType, valueType>::getCurrentValue ()
// {

//   return currentNode->value;

// }

// use node found at index i and add to list
// if already in list, then won't be added 
// because add function already ignores repeated keys 
template <class keyType, class valueType>
void Map<keyType, valueType>::merge(const Map<keyType, valueType> & other)
{

  
  for (int i = 0; i < other.counter; i++){

    MapItem<keyType, valueType>* newItem;
    newItem = other.get_node_at_index(i);
    add(newItem->key, newItem->value);
  }

}

// template <class keyType, class valueType>
// void Map<keyType, valueType>::printKeyOnly () const
// {
//   for(int i=0; i < counter; i++)
//   {
//     cout << this->get_node_at_index(i)->key << endl;
//   }

// }

template <class keyType, class valueType>
string Map<keyType, valueType>::printKeyOnly () const
{
  string returnString = "";
  for(int i=0; i < counter; i++)
  {
    returnString += this->get_node_at_index(i)->key + "\n";
  }

  return returnString;

}

#include "Set.h"

#endif