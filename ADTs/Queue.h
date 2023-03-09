#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue
{
public:
    // pre: -
    // post: the element is inserted at the end of the queue
    virtual void enqueue(T element) = 0;

    // pre: the quque is not empty
    // post: returns the last element of the queue
    virtual T next() = 0;

    // pre: the queue is not empty
    // post: returns the last element of the queue and removes it from the queue
    virtual T dequeue() = 0;

    // pre: -
    // post: returns if the queue is empty
    virtual bool isEmpty() = 0;
};

#endif