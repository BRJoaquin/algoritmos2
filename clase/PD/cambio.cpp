#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

int monedas[5] = {1, 2, 5, 10, 50};


void cambioTab(int cambioADevolver) {
    int * tab = new int[cambioADevolver + 1]();
    int * vengo = new int[cambioADevolver + 1]();
    tab[0] = 0;

    for (int cambioActual = 1; cambioActual <= cambioADevolver; cambioActual++)
    {
        int monedaQueUso = -1;
        int min = INT_MAX;
        for (int monedaIndex = 0; monedaIndex < 5; monedaIndex++)
        {
            if(monedas[monedaIndex] <= cambioActual) {
                int valorMoneda =  monedas[monedaIndex];
                if(tab[cambioActual-valorMoneda] < min) {
                    min = tab[cambioActual-valorMoneda];
                    monedaQueUso = monedaIndex;
                    vengo[cambioActual] = valorMoneda;
                }
            }else{
                break; // es solo porque estan ordenadas!!
            }
            tab[cambioActual] = 1 + tab[cambioActual - monedas[monedaQueUso]];
        }
    }

    

    cout << "Necesito " << tab[cambioADevolver] << " monedas" << endl;
    int estoy = cambioADevolver;
    while(estoy != 0) {
        int valorMonedaQueDoy = vengo[estoy];
        cout << "Dí la moneda de " << valorMonedaQueDoy << endl;
        estoy -= valorMonedaQueDoy;
    }
}

int main()
{
    cambioTab(13);
}