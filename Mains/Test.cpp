#include <cassert>
#include <string>
#include <iostream>
#include <limits>

#include "../Helpers/Iterator.h"

#include "../ADTs/List.h"
#include "../ADTs/ListImp.cpp"

#include "../ADTs/Queue.h"
#include "../ADTs/QueueImp.cpp"

#include "../DataStructures/BST.cpp"

#include "../DataStructures/AVL.cpp"

#include "../DataStructures/HashTable.h"
#include "../DataStructures/HashTableSeparateChaining.cpp"

using namespace std;

void listTest() {
    cout << "List test" << endl;
    List<int> *list = new ListImp<int>();
    for (int i = 0; i < 5; i++)
    {
        list->insert(i);
    }
    Iterator<int> *iterator = list->getIterator();
    while (iterator->hasNext())
    {
        cout << iterator->next() << endl;
    }
    delete iterator;
    delete list;
    cout << "List test finished" << endl << endl;
}

void queueTest() {
    cout << "Queue test" << endl;
    Queue<int> *queue = new QueueImp<int>();
    for (int i = 0; i < 5; i++)
    {
        queue->enqueue(i);
    }
    while (!queue->isEmpty())
    {
        cout << queue->dequeue() << endl;
    }
    delete queue;
    cout << "Queue test finished" << endl << endl;
}

void print(int element) {
    cout << element << endl;
}

void BSTTest() {
    cout << "BST test" << endl;
    BST<int> *bst = new BST<int>();
    for (int i = 0; i < 5; i++)
    {
        bst->insert(i);
    }
    bst->inOrder(print);
    delete bst;
    cout << "BST test finished" << endl << endl;
}

void AVLTest() {
    cout << "AVL test" << endl;
    AVL<int> *avl = new AVL<int>();
    for (int i = 0; i < 5; i++)
    {
        avl->insert(i);
    }
    avl->inOrder(print);
    delete avl;
    cout << "AVL test finished" << endl << endl;
}

int hashFn(string key) {
    int hash = 0;
    for (int i = 0; i < key.length(); i++)
    {
        hash += key[i];
    }
    return hash;
}

bool equalStrings(string key1, string key2) {
    return key1 == key2;
}

void HashTableTest() {
    cout << "HashTable test" << endl;
    HashTable<string, int> *hashTable = new HashTableSeparateChaining<string, int>(10, hashFn, equalStrings);
    hashTable->insert("a", 1);
    hashTable->insert("b", 2);
    hashTable->insert("c", 3);
    hashTable->insert("d", 4);


    cout << hashTable->get("a") << endl;
    cout << hashTable->get("b") << endl;
    cout << hashTable->get("c") << endl;

    hashTable->remove("a");

    Iterator<Tuple<string, int>> *it = hashTable->getIterator();
    while (it->hasNext())
    {
        Tuple<string, int> tuple = it->next();
        cout << tuple.getFirst() << " " << tuple.getSecond() << endl;
    }


    cout << "HashTable test finished" << endl << endl;
}

int main()
{
    listTest();
    queueTest();
    BSTTest();
    AVLTest();
    HashTableTest();
    return 0;
}