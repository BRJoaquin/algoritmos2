#ifndef LIST_H
#define LIST_H

#include "../Helpers/Iterator.h"

template <class T>
class List
{
public:
    // pre:
    // post: the element is inserted at the end of the list
    virtual void insert(T element) = 0;

    // pre: the index is valid (0 <= index < size)
    // post: the element is inserted at the given index
    virtual void insertAt(int index, T element) = 0;

    // pre: -
    // post: remove the first element that is equal to the given element
    virtual void remove(T element) = 0;

    // pre: the index is valid (0 <= index < size)
    // post: the element is removed at the given index
    virtual void removeAt(int index) = 0;


    virtual void empty() = 0;


    // pre: -
    // post: returns if the list is empty
    virtual bool isEmpty() = 0;

    // pre: the index is valid (0 <= index < size)
    // post: returns the element at the given index
    virtual T get(int index) = 0;

    // pre: -
    // post: returns the size of the list
    virtual int getSize() = 0;

    // pre: -
    // post: returns an iterator to the list
    virtual Iterator<T> *getIterator() = 0;
};

#endif