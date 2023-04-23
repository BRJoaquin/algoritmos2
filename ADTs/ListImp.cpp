#ifndef LIST_IMP
#define LIST_IMP

#include "List.h"
#include <cassert>

template <class T>
class ListImp : public List<T>
{
private:
    // define a inner class (Node) to be used by the double linked list
    class Node
    {
    public:
        T element;
        Node *next;
        Node *previous;
        Node(T element, Node *next, Node *previous) : element(element), next(next), previous(previous) {}
    };

    // implement an iterator for the list
    class ListIterator : public Iterator<T>
    {
    private:
        Node *current;

    public:
        ListIterator(Node *current) : current(current) {}
        bool hasNext()
        {
            return current != NULL;
        }
        T next()
        {
            T element = current->element;
            current = current->next;
            return element;
        }
    };

    Node *head;
    Node *tail;
    int size;

public:
    ListImp() : head(NULL), size(0) {}

    void insert(T element)
    {
        Node *newNode = new Node(element, NULL, this->tail);
        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insertAt(int index, T element)
    {
        assert(index >= 0 && index < size);
        Node *newNode = new Node(element, NULL, NULL);
        if (index == 0)
        {
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
        }
        else if (index == size)
        {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index; i++)
            {
                current = current->next;
            }
            newNode->next = current;
            newNode->previous = current->previous;
            current->previous->next = newNode;
            current->previous = newNode;
        }
        size++;
    }

    void remove(T element)
    {
        Node *current = head;
        while (current != NULL)
        {
            // note: that the elment should implement == operator
            if (current->element == element)
            {
                if (current == head)
                {
                    head = current->next;
                    if (head != NULL)
                    {
                        head->previous = NULL;
                    }
                }
                else if (current == tail)
                {
                    tail = current->previous;
                    if (tail != NULL)
                    {
                        tail->next = NULL;
                    }
                }
                else
                {
                    current->previous->next = current->next;
                    current->next->previous = current->previous;
                }
                delete current;
                size--;
                return;
            }
            current = current->next;
        }
    }

    void removeAt(int index)
    {
        assert(index >= 0 && index < size);
        Node *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        if (current == head)
        {
            head = current->next;
            if (head != NULL)
            {
                head->previous = NULL;
            }
        }
        else if (current == tail)
        {
            tail = current->previous;
            if (tail != NULL)
            {
                tail->next = NULL;
            }
        }
        else
        {
            current->previous->next = current->next;
            current->next->previous = current->previous;
        }
        delete current;
        size--;
    }

    bool isEmpty()
    {
        return head == NULL;
    }

    T get(int index)
    {
        assert(index >= 0 && index < size);
        Node *current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->element;
    }

    int getSize()
    {
        return size;
    }

    Iterator<T> *getIterator()
    {
        return new ListIterator(this->head);
    }
};

#endif