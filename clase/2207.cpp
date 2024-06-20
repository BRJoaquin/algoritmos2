#include <string>
#include <iostream>
#include <climits>
#include <cassert>
#include "../ADTs/List.h"
#include "../ADTs/ListImp.cpp"
using namespace std;

// Ejercicio 1

//  P(0) = P(1) = P(2) = 1
//  P(n) = P(n-2) + P(n-3)

long padovan_memo_rec(unsigned int n, long *memo)
{
    // caso base
    if (n <= 2)
    {
        return 1;
    }
    // pregunto si ya lo calcule
    if (memo[n] != -1)
    {
        memo[n] = padovan_memo_rec(n - 2, memo) + padovan_memo_rec(n - 3, memo);
    }
    return memo[n];
}

long padovan_memo(unsigned int n)
{
    long *memo = new long[n + 1]();
    for (int i = 0; i <= n; i++)
    {
        memo[i] = -1; // el valor del no calculado
    }

    return padovan_memo_rec(n, memo);
}

long padovan_tab(unsigned int n)
{
    long *tab = new long[n + 1]();
    // casos base
    tab[0] = 1;
    tab[1] = 1;
    tab[2] = 1;
    // pr
    for (int i = 3; i <= n; i++)
    {
        tab[i] = tab[i - 2] + tab[i - 3];
    }
    return tab[n];
}

// Ejercicio 2

bool tengoQuePodar(List<int> *solActual, List<int> *mejorSolucion)
{
    return mejorSolucion != NULL && solActual->getSize() > mejorSolucion->getSize();
}

int calcularSuma(List<int> *solActual)
{
    int sumando = 0;
    Iterator<int> *it = solActual->getIterator();
    while (it->hasNext())
    {
        int el = it->next();
        sumando += el;
    }
    return sumando;
}

bool esMejorSolucion(List<int> *solActual, List<int> *mejorSolucion)
{
    return mejorSolucion == NULL || solActual->getSize() < mejorSolucion->getSize();
}

bool esSolucion(List<int> *solActual, int M)
{
    return calcularSuma(solActual) == M;
}

List<int> *clonarSolucion(List<int> *solActual)
{
    return solActual->clone();
}

bool esMovimientoValido(int sumaAc, int el, int M)
{
    return (sumaAc + el) <= M;
}

void realizarMovimiento(int num, List<int> *actual)
{
    actual->insert(num);
}

void quitarMovimiento(int num, List<int> *actual)
{
    actual->removeAt(actual->getSize() - 1);
}

void sumatoriaBt(int *C, int N, int el, int M, List<int> *solActual, List<int> *&mejorSolucion)
{
    if (!tengoQuePodar(solActual, mejorSolucion) && el < N)
    {
        if (esSolucion(solActual, M) && esMejorSolucion(solActual, mejorSolucion))
        {
            mejorSolucion = clonarSolucion(solActual);
        }
        else
        {
            int sumaActual = calcularSuma(solActual);
            // movimientos posibles
            int numeroAUsar = C[el];
            for (int loUso = 0; loUso <= 1; loUso++)
            {
                if (loUso == 0)
                {
                    if (esMovimientoValido(sumaActual, numeroAUsar, M))
                    {
                        realizarMovimiento(numeroAUsar, solActual);
                        sumatoriaBt(C, N, el, M, solActual, mejorSolucion);
                        quitarMovimiento(numeroAUsar, solActual);
                    }
                }
                else
                {
                    sumatoriaBt(C, N, el + 1, M, solActual, mejorSolucion);
                }
            }
        }
    }
}

void imprimirSolucion(List<int> *lista)
{
    Iterator<int> *it = lista->getIterator();
    while (it->hasNext())
    {
        int el = it->next();
        cout << el << endl;
    }
}

void sumatoria(int *C, int N, int M)
{
    List<int> *sandbox = new ListImp<int>();
    List<int> *solucion = NULL;
    sumatoriaBt(C, N, 0, M, sandbox, solucion);
    if (solucion == NULL)
    {
        cout << "No existe" << endl;
    }
    else
    {
        imprimirSolucion(solucion);
    }
}

int main()
{
    int N = 3;
    int* C = new int[N]();
    C[0] = 3;
    C[1] = 5;
    C[2] = 20;
    int M = 3002;
    sumatoria(C, N, M);
}