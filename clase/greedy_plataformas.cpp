#include <string>
#include <iostream>
#include <climits>
#include <cassert>
#include "../DataStructures/MinHeap.cpp"

using namespace std;
#define INF INT_MAX;

#define CANT_TRENES 6

int arr[CANT_TRENES] = {900, 940, 950, 1100, 1500, 1800};
int dep[CANT_TRENES] = {910, 1200, 1120, 1130, 1900, 2000};

struct Evento
{
    int hora;
    char tipo;
};

int compararEventos(Evento e1, Evento e2)
{
    return e1.hora - e2.hora;
}

int plataformas()
{
    MinHeap<Evento> *heap = new MinHeap<Evento>(CANT_TRENES * 2, compararEventos);
    int cantPlataformas = 0;
    for (int i = 0; i < CANT_TRENES; i++)
    {
        Evento arribo = {arr[i], 'a'};
        Evento salida = {dep[i], 'd'};
        heap->insertar(arribo);
        heap->insertar(salida);
    }
    int suma = 0;
    while (!heap->estaVacio())
    {
        Evento sigEvento = heap->tope();
        heap->eliminarTope();
        if(sigEvento.tipo == 'a') {
            suma++;
        } else {
            suma--;
        }

        if(suma > cantPlataformas) {
            cantPlataformas = suma;
        }
    }

    return cantPlataformas;
}

int main()
{

    cout << plataformas() << endl;
}