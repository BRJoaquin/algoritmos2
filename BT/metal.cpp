#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

// cantidad de rocas
#define N 5


// capacidades
#define Al_MAX 100
#define Si_MAX 60
#define Fe_MAX 1000

// precios x kilo
#define Al_VALOR 166
#define Si_VALOR 223
#define Fe_VALOR 70

bool sePuedePodar() {
    return false;
}

bool esSolucion() {
    return true;
}

bool esMejorSolucion(int valorActual,int mejorValor) {
    return valorActual > mejorValor;
}

// evaluo si la composicion de la roca "entra" en lo que me resta de cada una de las capacidades
bool puedoMeterLaRoca(int capAl,int capSi,int capFe, int pesoAl, int pesoSi, int pesoFe) {
    return capAl >= pesoAl && capSi >= pesoSi && capFe >= pesoFe;
}

bool laUse(bool usada) {
    return usada;
}

void meterLaRoca(int &capAl, int &capSi, int &capFe, bool usados[N], int &valorActual, int pesoAl, int pesoSi, int pesoFe, int valorDeLaRoca, int rocaIndex) {
    capAl-=pesoAl;
    capSi-=pesoSi;
    capFe-=pesoFe;
    usados[rocaIndex] = true;
    valorActual+=valorDeLaRoca;
}
void sacarLaRoca(int &capAl, int &capSi, int &capFe, bool usados[N], int &valorActual, int pesoAl, int pesoSi, int pesoFe, int valorDeLaRoca, int rocaIndex) {
    capAl+=pesoAl;
    capSi+=pesoSi;
    capFe+=pesoFe;
    usados[rocaIndex] = false;
    valorActual-=valorDeLaRoca;
}

int calcularValorDeLaRoca(int pesoAl, int pesoSi, int pesoFe) {
    return pesoAl * Al_VALOR + pesoSi * Si_VALOR + pesoFe * Fe_VALOR;
}

void clonar(bool origen[N], bool destino[N]) {
    for (int i = 0; i < N; i++)
    {
        destino[i] = origen[i];
    }
}

void metal(int capAl, int capSi, int capFe, bool usados[N], int valorActual,int al[N], int si[N], int fe[N], int &mejorValor, bool mejorUsados[N])
{
    if (!sePuedePodar())
    {
        if (esSolucion() && esMejorSolucion(valorActual, mejorValor))
        {
            clonar(usados, mejorUsados);
            mejorValor = valorActual;
        }
        else
        {
            // que movimientos puedo hacer ? (8 posibilidades)
            // para cada movimiento que puedo hacer
            for (int i = 0; i < N; i++)
            {
                if (!laUse(usados[i])  && puedoMeterLaRoca(capAl, capSi, capFe, al[i], si[i], fe[i]))
                {
                    int valorDeLaRoca = calcularValorDeLaRoca(al[i], si[i], fe[i]);
                    meterLaRoca(capAl,capSi,capFe, usados, valorActual,al[i], si[i], fe[i],valorDeLaRoca, i  );
                    metal(capAl,capSi,capFe,usados, valorActual,al,si,fe,mejorValor, mejorUsados);
                    sacarLaRoca(capAl,capSi,capFe, usados, valorActual,al[i], si[i], fe[i],valorDeLaRoca, i  );
                }
            }
        }
    }
}

int main()
{
    int valorDeLaMochila = 0;
    int capAl = Al_MAX;
    int capSi = Si_MAX;
    int capFe = Fe_MAX;
    bool * usados = new bool[N]();
    bool * losUsados = new bool[N]();
    for (int i = 0; i < N; i++)
    {
       usados[i] = false;
       losUsados[i] = false;
    }
    int ai[N] = {20, 10, 30, 50, 0};
    int si[N] = {10, 20, 50, 70, 0};
    int fe[N] = {80, 90, 50, 10, 20};
    metal(capAl, capSi, capFe, usados, 0, ai, si, fe, valorDeLaMochila, losUsados);

    cout << valorDeLaMochila << endl;

    for (int i = 0; i < N; i++)
    {
        if(losUsados[i]) {
            cout << "Use la roca de index: " << i << endl;
        }
    }
    
    return 0;
}