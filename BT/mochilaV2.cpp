#include <string>
#include <iostream>
using namespace std;

bool sePuedeMeterEnLaMochila(int objetoAEvaluar, int *pesos, int capacidad)
{
    return pesos[objetoAEvaluar] <= capacidad;
}
void colocarEnLaMochila(int objetoAEvaluar, int &capacidad, int &valorActual, bool solucion[], int *pesos, int *valores)
{
    capacidad -= pesos[objetoAEvaluar];
    valorActual += valores[objetoAEvaluar];
    solucion[objetoAEvaluar] = true;
}
void sacarloDeLaMochila(int objetoAEvaluar, int &capacidad, int &valorActual, bool solucion[], int *pesos, int *valores)
{
    capacidad += pesos[objetoAEvaluar];
    valorActual -= valores[objetoAEvaluar];
    solucion[objetoAEvaluar] = false;
}

bool esSolucion()
{
    return true;
}

bool esMejorSolucion(int actual, int mejor)
{
    return actual > mejor;
}

void clonar(bool *origen, bool *destino, int N)
{
    for (int i = 0; i < N; i++)
    {
        destino[i] = origen[i];
    }
}

void mochila(int objetoAEvaluar, int N, int capacidad, int valorActual, int *pesos, int *valores, bool solucion[4], int &mejorValor, bool mejorSolucion[4])
{
    if (objetoAEvaluar + 1 < N)
    {
        if (sePuedeMeterEnLaMochila(objetoAEvaluar, pesos, capacidad))
        {
            colocarEnLaMochila(objetoAEvaluar, capacidad, valorActual, solucion, pesos, valores);
            if (esSolucion() && esMejorSolucion(valorActual, mejorValor))
            {
                clonar(solucion, mejorSolucion, N);

                mejorValor = valorActual;
            }
            // trato de usar el objeto
            mochila(objetoAEvaluar + 1, N, capacidad, valorActual, pesos, valores, solucion, mejorValor, mejorSolucion);
            sacarloDeLaMochila(objetoAEvaluar, capacidad, valorActual, solucion, pesos, valores);
            // no usando el objeto
            mochila(objetoAEvaluar + 1, N, capacidad, valorActual, pesos, valores, solucion, mejorValor, mejorSolucion);
        }
        else
        {
            // intentar con el resto
            mochila(objetoAEvaluar + 1, N, capacidad, valorActual, pesos, valores, solucion, mejorValor, mejorSolucion);
        }
    }
}

int main()
{
    int const N = 4;
    int pesos[N] = {5, 3, 8, 4};
    int valores[N] = {10, 20, 25, 8};
    int capacidadMochila = 13;
    bool playground[N] = {false, false, false, false};
    bool solucion[N] = {false, false, false, false};
    int valorDeLaMochila = 0;
    mochila(0, N, capacidadMochila, 0, pesos, valores, playground, valorDeLaMochila, solucion);
    cout << valorDeLaMochila << endl;
    for (int i = 0; i < N; i++)
    {
        if(solucion[i]) {
            cout << "Use el objeto " << (i+1) << endl;
        }
    }
    
    return 0;
}