#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

int CANT_MONEDAS = 5;
int MONEDAS[5] = {1, 2, 5, 10, 50};

// DAC
int cambio_dac(int monedaHasta, int cambio) {
    if(cambio == 0) {
        return 0;
    }
    if(monedaHasta < 0) {
        return INT_MAX;
    }
    
    if(MONEDAS[monedaHasta] > cambio) {
        return cambio_dac(monedaHasta - 1, cambio);
    }

    int cantMonedasSiUso = 1 + cambio_dac(monedaHasta, cambio - MONEDAS[monedaHasta]);
    int cantMonedasNoUso = cambio_dac(monedaHasta - 1, cambio);

    return min(cantMonedasSiUso, cantMonedasNoUso);
}


// MEMOIZACION
int cambio_memo(int monedaHasta, int cambio, int** memo) {
    if(cambio == 0) {
        return 0;
    }
    if(monedaHasta < 0) {
        return INT_MAX;
    }

    if(memo[monedaHasta][cambio] != -1) {
        return memo[monedaHasta][cambio];
    }
    
    if(MONEDAS[monedaHasta] > cambio) {
        memo[monedaHasta][cambio] = cambio_memo(monedaHasta - 1, cambio, memo);
        return memo[monedaHasta][cambio];
    }

    int cantMonedasSiUso = 1 + cambio_memo(monedaHasta, cambio - MONEDAS[monedaHasta], memo);
    int cantMonedasNoUso = cambio_memo(monedaHasta - 1, cambio, memo);

    memo[monedaHasta][cambio] = min(cantMonedasSiUso, cantMonedasNoUso);
    return memo[monedaHasta][cambio];
}

int **initMatriz(int cambio)
{
    int **matriz = new int *[CANT_MONEDAS + 1]();
    for (int f = 0; f < CANT_MONEDAS + 1; f++)
    {
        matriz[f] = new int[cambio + 1]();
        for (int c = 0; c < cambio + 1; c++)
        {
            matriz[f][c] = -1;
        }
        
    }
    return matriz;
}

int cambio_tab(int cambio) {
    int** tab = initMatriz(cambio);
    // caso base
    for (int m = 0; m < CANT_MONEDAS; m++)
    {
        tab[m][0] = 0;
    }
    // "paso recursivo"
    for (int m = 0; m < CANT_MONEDAS; m++)
    {
        for (int c = 1; c <= cambio; c++)
        {
            int valorMonedaActual = MONEDAS[m];
            if(valorMonedaActual > c) {
                tab[m][c] = tab[m-1][c];
            } else {
                int cantMonedasSiUso = 1 + tab[m][c-valorMonedaActual];
                int cantMonedasNoUso = m == 0 ? INT_MAX : tab[m-1][c];
                tab[m][c] = min(cantMonedasSiUso, cantMonedasNoUso);
            }
        }
    }
    return tab[CANT_MONEDAS - 1][cambio];
}

int cambio_tab2(int cambio) {
    int* tab = new int[cambio+1]();
    // caso base
    tab[0] = 0;
    // "paso recursivo"
    for (int c = 1; c <= cambio; c++)
    {
        int cambioMinimo = INT_MAX;
        for (int m = 0; m < CANT_MONEDAS; m++)
        {
            int valorMoneda = MONEDAS[m];
            // si podemos usar la moneda
            if(c >= valorMoneda) {
                cambioMinimo = min(cambioMinimo, 1 + tab[c-valorMoneda]);
            }
        }
        tab[c] = cambioMinimo;
    }
    return tab[cambio];
}

int cambio_tab_camino(int cambio) {
    int* tab = new int[cambio+1]();
    int* use = new int[CANT_MONEDAS]();
    for (int i = 0; i < CANT_MONEDAS; i++)
    {
        use[i] = 0;
    }
    
    // caso base
    tab[0] = 0;
    // "paso recursivo"
    for (int c = 1; c <= cambio; c++)
    {
        int cambioMinimo = INT_MAX;
        int monedaUsadaIndex = -1;
        for (int m = 0; m < CANT_MONEDAS; m++)
        {
            int valorMoneda = MONEDAS[m];
            // si podemos usar la moneda
            if(c >= valorMoneda) {
                // cambioMinimo = min(cambioMinimo, 1 + tab[c-valorMoneda]);
                if(cambioMinimo > 1 + tab[c-valorMoneda]) {
                    cambioMinimo = 1 + tab[c-valorMoneda];
                }
            }
        }
        tab[c] = cambioMinimo;
    }

    for (int i = 0; i < CANT_MONEDAS; i++)
    {
        if(use[i] > 0) {
            cout << "Use " << use[i] << " moneda/s de " << MONEDAS[i] << endl;
        }
    }
    

    return tab[cambio];
}


int main()
{
    int cambio = 47;
    // cout << cambio_dac(CANT_MONEDAS - 1, 5000) << endl;
    // int** memo = initMatriz(cambio);
    // cout << cambio_memo(CANT_MONEDAS - 1, cambio, memo) << endl;
    // cout << cambio_tab(cambio) << endl;
    // cout << cambio_tab2(cambio) << endl;
    cout << cambio_tab_camino(cambio) << endl;

    

}