#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

#include "../DataStructures/AVL.cpp"

void imprimirFn(int el) {
    cout << el << endl;
}

int main()
{
    AVL<int> * arbolito = new AVL<int>();
    arbolito->insert(20);
    arbolito->insert(80);
    arbolito->insert(10);
    arbolito->insert(5);
    arbolito->insert(300);

    arbolito->inOrder(imprimirFn);
}