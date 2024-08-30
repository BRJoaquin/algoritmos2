#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "./Table.h"
#include "./HashAbierto.cpp"
#include "./HashCerrado.cpp"


using namespace std;

int hash1(string key) {
  int h = 0;
  for (int i = 0; i < key.length(); i++)
    h = h + key[i];
  return h;
}

int main()
{
    Table<string, int> * tabla = new HashCerrado<string, int>(10, hash1);
    tabla->insert("AAA", 222);
    tabla->insert("BBB", 333);

    cout << tabla->exists("AAA") << endl;
    cout << tabla->get("BBC") << endl;

}