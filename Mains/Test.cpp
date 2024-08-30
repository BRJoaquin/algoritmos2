#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../DataStructures/AVL.cpp"
using namespace std;

class Persona {
    public:
        int edad;
        string nombre;
        Persona(int unaEdad, string unNombre) {
            this->edad =  unaEdad;
            this->nombre = unNombre;
        }
};

int main()
{
    AVL<Persona> * arbolito = new AVL<Persona>();
    arbolito->insert(2);
    return 0;
}