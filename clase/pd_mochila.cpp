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

int** initMatriz(int objetoHasta, int capacidad){
    int **matriz = new int *[objetoHasta + 2]();
    for (int f = 0; f < objetoHasta + 2; f++)
    {
        matriz[f] = new int[capacidad + 1]();
    }
    return matriz;
}

int mochila01_tab(int objetoHasta, int capacidad) {
    int** tab = initMatriz(objetoHasta, capacidad);

    // no tengo ningun objeto
    for (int capActual = 0; capActual <= capacidad; capActual++)
    {
        tab[0][capActual] = 0;
    }

    // no tengo ningun objeto
    for (int objetoActual = 1; objetoActual <= objetoHasta; objetoActual++)
    {
        int valorObjetoHasta = valores[objetoActual - 1];
        int pesoObjetoHasta = pesos[objetoActual - 1];
        for (int capActual = 0; capActual <= capacidad; capActual++)
        {
            if(capActual < pesoObjetoHasta) {
                tab[objetoActual][capActual] = tab[objetoActual - 1][capActual];
            } else {
                int valorPonerObjeto = valorObjetoHasta + tab[objetoActual - 1][capActual - pesoObjetoHasta];
                int valorNoPonerObjeto = tab[objetoActual - 1][capActual];
                tab[objetoActual][capActual] = valorPonerObjeto > valorNoPonerObjeto ? valorPonerObjeto : valorNoPonerObjeto;
            }
        }
    }

    return tab[objetoHasta + 1][capacidad];
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