#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

int N = 4;
string nombres[4] = {"ruby", "lingote", "diamante", "moneda"};
int pesos[4] = {8, 5, 3, 4};
int valores[4] = {25, 10, 20, 8};
int capacidad = 13;

bool tengoQuePodar()
{
    return false;
}

bool esSolucion(int objActual)
{
    return objActual == N;
}

int pesoMochila(bool *usados)
{
    int peso = 0;
    for (int i = 0; i < N; i++)
    {
        if (usados[i])
        {
            peso += pesos[i];
        }
    }
    return peso;
}

int valorMochila(bool *usados)
{
    int valor = 0;
    for (int i = 0; i < N; i++)
    {
        if (usados[i])
        {
            valor += valores[i];
        }
    }
    return valor;
}

bool esMejorSolucion(bool *usados, bool *mejorUsados)
{
    return valorMochila(usados) > valorMochila(mejorUsados);
}

void clonarSolucion(bool *usados, bool *mejorUsados)
{
    for (int i = 0; i < N; i++)
    {
        mejorUsados[i] = usados[i];
    }
}

bool puedoPonerObjeto(bool *usados, int objActual)
{
    return pesoMochila(usados) + pesos[objActual] <= capacidad;
}

void aplicarMovimiento(bool *usados, int objActual)
{
    usados[objActual] = true;
}

void deshacerMovimiento(bool *usados, int objActual)
{
    usados[objActual] = false;
}

void mochila01(int objActual, bool *usados, bool *mejorUsados)
{
    if (!tengoQuePodar())
    {
        if (esSolucion(objActual))
        {
            if(esMejorSolucion(usados, mejorUsados)) {
                clonarSolucion(usados, mejorUsados);
            }
        }
        else
        {
            // pongo el objeto
            if (puedoPonerObjeto(usados, objActual))
            {
                aplicarMovimiento(usados, objActual);
                mochila01(objActual + 1, usados, mejorUsados);
                deshacerMovimiento(usados, objActual);
            }

            // no pongo el objeto
            mochila01(objActual + 1, usados, mejorUsados);
        }
    }
}

int main()
{
    bool *usados = new bool[N]();
    bool *mejorUsados = new bool[N]();
    for (int i = 0; i < N; i++)
    {
        usados[i] = false;
        mejorUsados[i] = false;
    }
    

    mochila01(0, usados, mejorUsados);
    for (int i = 0; i < N; i++)
    {
        if (mejorUsados[i])
        {
            cout << "Use el objeto " << nombres[i] << endl;
        }
    }
}