#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

int* pesos = new int[4]();
int* volumen = new int[4]();
int* valores = new int[4]();
int capacidadPeso = 8;
int capacidadVolumen = 5;


int max(int a, int b) {
    return a > b ? a : b;
}

int mochila(int capPesoAct, int capVolAct, int n) {
    if(capPesoAct == 0 || capVolAct == 0 || n < 0) {
        return 0;
    }

    // si no entra el objeto lo descarto
    if(pesos[n] > capPesoAct || volumen[n] > capVolAct) {
        return mochila(capPesoAct, capVolAct, n-1);
    }

    int usandoObjeto = valores[n] + mochila(capPesoAct - pesos[n], capVolAct - volumen[n], n - 1);
    int noUsandoObjeto = mochila(capPesoAct, capVolAct, n-1);

    return max(usandoObjeto, noUsandoObjeto);
}


int main()
{ 
    pesos[0] = 2;
    valores[0] = 5;
    volumen[0] = 1;

    pesos[1] = 3;
    valores[1] = 4;
    volumen[1] = 2;

    pesos[2] = 4;
    valores[2] = 4;
    volumen[2] = 3;

    pesos[3] = 5;
    valores[3] = 10;
    volumen[3] = 4;

    cout << mochila(capacidadPeso, capacidadVolumen, 3) << endl;
}