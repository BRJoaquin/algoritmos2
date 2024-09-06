#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "./Table.h"
#include "./HashAbierto.cpp"
#include "./HashCerrado.cpp"
#include "./MinHeap.cpp"

using namespace std;

class Persona
{
public:
  string nombre;
  int edad;
  int pac;
  Persona(string _nombre, int _edad, int _pac)
  {
    this->nombre = _nombre;
    this->edad = _edad;
    this->pac = _pac;
  }
  Persona() {}
};

int comparacionInt(int a, int b)
{
  return a - b;
}

int comparacionPersonaPorEdad(Persona a, Persona b)
{
  return b.edad - a.edad;
}

int comparacionPersonaPorPac(Persona a, Persona b)
{
  return b.pac - a.pac;
}

int main()
{
  MinHeap<Persona> *heap = new MinHeap<Persona>(10, comparacionPersonaPorPac);
  Persona p1("pepe", 22, 90);
  heap->insertar(p1);
  Persona p2("juan", 33, 45);
  heap->insertar(p2);
  Persona p3("ana", 35, 80);
  heap->insertar(p3);
  Persona p4("joaquin", 25, 50);
  heap->insertar(p4);

  while (!heap->estaVacio())
  {
    Persona el = heap->tope();
    heap->eliminar();
    cout << el.nombre << " " << el.edad <<  " " << el.pac << endl;
  }
}