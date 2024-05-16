#include <string>
#include <iostream>
#include <climits>
#include <cassert>
#define INF INT_MAX;
using namespace std;


int CAPACIDAD = 12;

int   pesos[4] = { 4, 10, 1, 20};
int valores[4] = { 5,  8, 4, 12};


int mochila01(int objetoHasta, int capacidad) {
    // si yo no tengo objetos o me quede sin capacidad
    if(objetoHasta < 0 || capacidad == 0) {
        return 0;
    }
    // si a mi no me entra el opbjeto lo ignoro
    if(capacidad < pesos[objetoHasta]) {
        return mochila01(objetoHasta-1, capacidad);
    }

    int valorDePonerElObjeto = valores[objetoHasta] + mochila01(objetoHasta - 1, capacidad - pesos[objetoHasta]);
    int valorDeNOPonerElObjeto = mochila01(objetoHasta - 1, capacidad);

    return max(valorDePonerElObjeto, valorDeNOPonerElObjeto);
}


int mochila0Inf(int objetoHasta, int capacidad) {
    // si yo no tengo objetos o me quede sin capacidad
    if(objetoHasta < 0 || capacidad == 0) {
        return 0;
    }
    // si a mi no me entra el opbjeto lo ignoro
    if(capacidad < pesos[objetoHasta]) {
        return mochila0Inf(objetoHasta-1, capacidad);
    }

    int valorDePonerElObjeto = valores[objetoHasta] + mochila0Inf(objetoHasta, capacidad - pesos[objetoHasta]);
    int valorDeNOPonerElObjeto = mochila0Inf(objetoHasta - 1, capacidad);

    return max(valorDePonerElObjeto, valorDeNOPonerElObjeto);
}


int main()
{
    cout << mochila0Inf(3, 12) << endl;
}