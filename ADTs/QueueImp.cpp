#ifndef QUEUE_IMP
#define QUEUE_IMP

#include "Queue.h"
#include <cassert>

template <class T>
class QueueImp : public Queue<T>
{
private:
    class Node
    {
    public:
        T element;
        Node *next;
        Node *previous;
        Node(T element, Node *previous, Node *next) : element(element), previous(previous), next(next) {}
    };
    Node *front, *back;
    int size;

public:
    // front(older) <-> ... <-> back (newer)
    QueueImp() : front(NULL), back(NULL), size(0) {}

    void enqueue(T element)
    {
        Node *newNode = new Node(element, NULL, back);
        if (isEmpty())
        {
            front = newNode;
            back = newNode;
        }
        else
        {
            back->previous = newNode;
            back = newNode;
        }
        size++;
    }

    T next()
    {
        assert(!this->isEmpty());
        return front->element;
    }

    T dequeue()
    {
        assert(!this->isEmpty());
        T element = front->element;
        Node *toDelete = front;
        front = front->previous;
        if (front == NULL)
        {
            back = NULL;
        }
        delete toDelete;
        size--;
        return element;
    }

    bool isEmpty()
    {
        return front == NULL;
    }
};

#endif