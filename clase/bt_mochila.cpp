#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

const int N = 100;

int CAPACIDAD_PESO = 50;

int random(int min, int max)
{
    return min + (std::rand() % (max - min + 1));
}

int* generarArray(int min, int max) {
    int* arr = new int[100]();
    for (int i = 0; i < N; i++)
    {
        arr[i] = random(min, max);
    }
    return arr;
}

int *valores = generarArray(1, 100);
int *pesos = generarArray(3, 20);

bool tengoQuePodar()
{
    return false; // no puedo podar cuando estoy maximizando
}

bool esSolucion(int objetoActual)
{
    return objetoActual == N;
}

bool esMejorSolucion(int valorActual, int mejorValor)
{
    return valorActual > mejorValor;
}

void clonarSolucion(bool origen[N], bool destino[N])
{
    for (int i = 0; i < N; i++)
    {
        destino[i] = origen[i];
    }
}

bool puedoUsarElObjeto(int capacidadActual, int pesoDelObjeto)
{
    return capacidadActual >= pesoDelObjeto;
}

void usarObjeto(int &capacidadActual, int &valorActual, bool usadosActual[N], int objetoActual)
{
    int valorObjeto = valores[objetoActual];
    int pesoObjeto = pesos[objetoActual];
    valorActual += valorObjeto;
    capacidadActual -= pesoObjeto;
    usadosActual[objetoActual] = true;
}

void quitarObjeto(int &capacidadActual, int &valorActual, bool usadosActual[N], int objetoActual)
{
    int valorObjeto = valores[objetoActual];
    int pesoObjeto = pesos[objetoActual];
    valorActual -= valorObjeto;
    capacidadActual += pesoObjeto;
    usadosActual[objetoActual] = false;
}

void mochila(int objetoActual, int capacidadActual, int valorActual, bool usadosActual[N], int &mejorValor, bool mejorUsados[N])
{
    if (!tengoQuePodar() && objetoActual <= N)
    {
        if (esSolucion(objetoActual) && esMejorSolucion(valorActual, mejorValor))
        {
            clonarSolucion(usadosActual, mejorUsados);
            mejorValor = valorActual;
        }
        else
        {
            // movimientos posibles
            for (int i = 0; i <= 1; i++)
            {
                bool loUso = i == 0;
                if (loUso)
                {
                    if (puedoUsarElObjeto(capacidadActual, pesos[objetoActual]))
                    {
                        usarObjeto(capacidadActual, valorActual, usadosActual, objetoActual);
                        mochila(objetoActual + 1, capacidadActual, valorActual, usadosActual, mejorValor, mejorUsados);
                        quitarObjeto(capacidadActual, valorActual, usadosActual, objetoActual);
                    }
                }
                else
                {
                    mochila(objetoActual + 1, capacidadActual, valorActual, usadosActual, mejorValor, mejorUsados);
                }
            }
        }
    }
}

int main()
{
    bool * usadosSandbox = new bool[N]();
    bool * mejorUsados = new bool[N]();
    int mejorValor = 0;

    mochila(0, CAPACIDAD_PESO,  0, usadosSandbox, mejorValor, mejorUsados);

    cout << "El valor que recolecte es de " << mejorValor << endl;
}