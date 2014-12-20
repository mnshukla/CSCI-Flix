#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
struct Node
{

  T data;
  Node<T> *next;

};

// class NoSuchElementException : public std::exception
// {

// };

template <class T>
class Queue {
  public:

    Queue();

    ~Queue();

    void enqueue (const T & item);
      /* adds the item to the end of the queue.
         The same item may be added many times. */

    void dequeue (); 
      /* removes the front element of the queue. 
         Throws an EmptyQueueException when called on an empty queue.
         EmptyQueueException should inherit from std::exception. */

    const T & peekFront ();
      /* returns the front element of the queue. 
         Throws an EmptyQueueException when called on an empty queue.
         EmptyQueueException should inherit from std::exception. */

    bool isEmpty ();
      /* returns whether the queue is empty. */

    int size();

  private:
    Node<T> *front, *back;
    int counter;

};

template <class T>
Queue<T>::Queue ()
{
  front = NULL;
  back = NULL;
  counter = 0;

}

template <class T>
Queue<T>::~Queue ()
{
  while (counter != 0)
  {
    this->dequeue();
  }
}

// returns numeber of elements in queue
template <class T>
int Queue<T>::size()
{
  return counter;
}

template <class T>
bool Queue<T>::isEmpty()
{
  if (counter == 0)
  {
    return true;
  }
  return false;
}

template <class T>
void Queue<T>::enqueue (const T & item)
{
  Node<T> *addNode = new Node<T>;

  addNode->data = item;
  addNode->next = NULL;

  if (front == NULL)
  {
    front = back = addNode;
  }
  else
  {
    back->next = addNode;
    back = addNode;
  }
  counter++;
}

template <class T>
void Queue<T>::dequeue()
{
  if (isEmpty())
  {
    NoSuchElementException e;
    throw (e);
  }
  else
  {
    Node<T> *deleteNode = new Node<T>;
    deleteNode = front;
    front = front->next;
    delete deleteNode;
  }
  counter--;
}

template <class T>
const T & Queue<T>::peekFront()
{
  // Node<T> *peek = new Node<T>;
  // peek = front;

  if (isEmpty())
  {
    NoSuchElementException e;
    throw (e);
  }
    return front->data;

}

#endif