#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "../../ADTs/List.h"
#include "../../ADTs/ListImp.cpp"
using namespace std;

struct Celda
{
    int f;
    int c;
    Celda(int uF, int uC)
    {
        f = uF;
        c = uC;
    }
};

struct Solucion
{
    List<Celda> *camino;
    int pasosSalsa;
    Solucion()
    {
        camino = new ListImp<Celda>();
        pasosSalsa = -1;
    }

    int pasos()
    {
        return this->camino->getSize();
    }
};

bool tengoQuePodar(Solucion *candidata, Solucion *mejorSolucion, int nRestantes)
{
    return mejorSolucion != NULL && candidata->pasos() + nRestantes > mejorSolucion->pasos();
}

bool esSolucion(Solucion *candidata, int nRestantes)
{
    return nRestantes == 0 && candidata->pasosSalsa >= 0;
}

bool esMejorSolucion(Solucion *candidata, Solucion *mejorSolucion)
{
    return mejorSolucion == NULL || (candidata->pasos() < mejorSolucion->pasos()) ||
           (candidata->pasos() == mejorSolucion->pasos() && candidata->pasosSalsa < mejorSolucion->pasosSalsa);
}

void clonar(Solucion *candidata, Solucion *&mejorSolucion)
{
    mejorSolucion = new Solucion();
    mejorSolucion->pasosSalsa = candidata->pasosSalsa;
    Iterator<Celda> *it = mejorSolucion->camino->getIterator();
    while (it->hasNext())
    {
        Celda aux = it->next();
        mejorSolucion->camino->insert(aux);
    }
}

bool coordenadaValida(Celda c)
{
    return c.f >= 0 && c.f < 7 && c.c >= 0 && c.c < 7;
}

bool esPared(Celda nueva, char tab[7][7])
{
    return tab[nueva.f][nueva.c] == 'P';
}

bool paseTresVeces(Celda nueva, int pase[7][7])
{
    return pase[nueva.f][nueva.c] >= 3;
}

bool puedoAplicarMov(Celda nueva, char tab[7][7], int pase[7][7])
{
    return coordenadaValida(nueva) && !esPared(nueva, tab) && !paseTresVeces(nueva, pase);
}

void aplicarMov(Celda nueva, char tab[7][7], int pase[7][7], int &nRestantes, Solucion *candidata)
{
    pase[nueva.f][nueva.c] += 1;
    candidata->camino->insert(nueva);
    if (tab[nueva.f][nueva.c] == 'N' && pase[nueva.f][nueva.c] == 1)
    {
        nRestantes--;
    }
    if (tab[nueva.f][nueva.c] == 'S' && pase[nueva.f][nueva.c] == 1)
    {
        candidata->pasosSalsa = candidata->pasos();
    }
}

void deshacerMov(Celda nueva, char tab[7][7], int pase[7][7], int &nRestantes, Solucion *candidata)
{
    pase[nueva.f][nueva.c] -= 1;
    candidata->camino->removeAt(candidata->camino->getSize() - 1);
    if (tab[nueva.f][nueva.c] == 'N' && pase[nueva.f][nueva.c] == 0)
    {
        nRestantes++;
    }
    if (tab[nueva.f][nueva.c] == 'S' && pase[nueva.f][nueva.c] == 0)
    {
        candidata->pasosSalsa = -1;
    }
}

void pacmanBT(char tab[7][7], int pase[7][7], Celda celdaActual, int nRestantes, Solucion *candidata, Solucion *mejorSolucion)
{
    if (!tengoQuePodar(candidata, mejorSolucion, nRestantes))
    {
        if (esSolucion(candidata, nRestantes))
        {
            if (esMejorSolucion(candidata, mejorSolucion))
            {
                clonar(candidata, mejorSolucion);
            }
        }
        else
        {
            int dF[4] = {-1, 1, 0, 0};
            int dC[4] = {0, 0, -1, 1};
            for (int i = 0; i < 4; i++)
            {
                Celda nueva(celdaActual.f + dF[i], celdaActual.c + dC[i]);
                if (puedoAplicarMov(nueva, tab, pase))
                {
                    aplicarMov(nueva, tab, pase, nRestantes, candidata);
                    pacmanBT(tab, pase, nueva, nRestantes, candidata, mejorSolucion);
                    deshacerMov(nueva, tab, pase, nRestantes, candidata);
                }
            }
        }
    }
}

List<Celda> *pacman(char tab[7][7])
{
    Celda inicial(0, 0);
    int pase[7][7];
    int nRestantes = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            pase[i][j] = 0;
            if (tab[i][j] == 'N')
            {
                nRestantes++;
            }
        }
    }
    Solucion *candidata = new Solucion();
    candidata->camino->insert(inicial);
    Solucion *mejorSolucion = NULL;
    pacmanBT(tab, pase, inicial, nRestantes, candidata, mejorSolucion);
    if (mejorSolucion == NULL)
    {
        return NULL;
    }
    return mejorSolucion->camino;
}

int main()
{
}