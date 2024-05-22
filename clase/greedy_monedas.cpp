#include <string>
#include <iostream>
#include <climits>
#include <cassert>

using namespace std;

int monedas[5] = {1, 2, 5, 10, 50};
int cantidadMonedas = 5;


int* cambio(int cambioADevolver) {
    int monedaIndex = cantidadMonedas - 1;
    int* monedasUsadas =  new int[cantidadMonedas]();
    while(cambioADevolver > 0) {
        if(monedas[monedaIndex] <= cambioADevolver) {
            cambioADevolver -= monedas[monedaIndex];
            monedasUsadas[monedaIndex]++;
        } else {
            monedaIndex--;
        }
    }
    return monedasUsadas;
}


int main()
{
    int* monedasUsadas = cambio(47);
    for (int i = cantidadMonedas-1; i >= 0; i--)
    {
        if(monedasUsadas[i] > 0) {
            cout << "Use " << monedasUsadas[i] << " moneda/s de " << monedas[i] << endl;
        }
    }
    
}