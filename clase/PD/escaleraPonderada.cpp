#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int min(int a, int b)
{
    return a < b ? a : b;
}

int camino(int *costo, int N)
{
    int *tab = new int[N]();
    tab[0] = costo[0];
    tab[1] = costo[0] + costo[1];
    for (int i = 2; i < N; i++)
    {
        tab[i] = min(tab[i - 1], tab[i - 2]) + costo[i];
    }

    return tab[N - 1];
}

void imprimirCamino(int estoy, int* vengo) {
    if(estoy != -1){
        imprimirCamino(vengo[estoy], vengo);
        cout << "->" << estoy;
    }
    
}

void caminoV2(int *costo, int N)
{
    int *tab = new int[N]();
    int *vengo = new int[N]();
    tab[0] = costo[0];
    vengo[0] = -1;
    tab[1] = costo[0] + costo[1];
    vengo[1] = 0;

    for (int i = 2; i < N; i++)
    {
        if (tab[i - 1] < tab[i - 2])
        {
            tab[i] = tab[i - 1] + costo[i];
            vengo[i] = i - 1;
        }
        else
        {
            tab[i] = tab[i - 2] + costo[i];
            vengo[i] = i - 2;
        }
    }

    cout << "El costo es " << tab[N-1] << endl;
    imprimirCamino(N-1, vengo);
    cout << endl;
}

void caminoV3(int *costo, int N)
{
    int *tab = new int[N]();
    tab[0] = costo[0];
    tab[1] = costo[0] + costo[1];
    for (int i = 2; i < N; i++)
    {
        tab[i] = min(tab[i - 1], tab[i - 2]) + costo[i];
    }

    cout << "El costo es " << tab[N-1] << endl;
    int estoy = N - 1;
    while(estoy != -1) {
        cout << "->" << estoy;
        if(estoy == 1) {
            estoy = 0;
        }else if(estoy == 0) {
            estoy = - 1;
        }else if(tab[estoy - 1] < tab[estoy - 2]) {
            estoy = estoy - 1;
        } else {
            estoy = estoy - 2;
        }
    }
    cout << endl;
}

int main()
{
    int costo[9] = {5, 2, 8, 7, 3, 2, 12, 21, 3};
    // cout << camino(costo, 9) << endl;
    // caminoV2(costo, 9);
    caminoV3(costo, 9);

}