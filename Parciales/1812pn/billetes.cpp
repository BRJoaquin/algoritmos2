#include <string>
#include <iostream>
#include <climits>
using namespace std;

#define INF INT_MAX;

bool esSolucion(int cambioRestante)
{
    return cambioRestante == 0;
}
bool esMejorSolucion(int cantBilletes, int mejorCantBilletes)
{
    return cantBilletes < mejorCantBilletes;
}
bool hayQuePodar(int cantBilletes, int mejorCantBilletes)
{
    return cantBilletes > mejorCantBilletes;
}
bool esMovimientoValido(int index, int cambioRestante, int billetes[6], int cantidades[6])
{
    return billetes[index] <= cambioRestante && cantidades[index] > 0;
}
void aplicarMovimiento(int index, int &cambioRestante, int billetes[6], int cantidades[6], int &cantBilletes, int usados[6])
{
    cambioRestante -= billetes[index];
    cantidades[index]--;
    cantBilletes++;
    usados[index]++;
}
void retirarMovimiento(int index, int &cambioRestante, int billetes[6], int cantidades[6], int &cantBilletes, int usados[6])
{
    cambioRestante += billetes[index];
    cantidades[index]++;
    cantBilletes--;
    usados[index]--;
}
void clonarSolucion(int original[6], int destino[6])
{
    for (int i = 0; i < 6; i++)
    {
        destino[i] = original[i];
    }
}

void cambioBT(int cambioRestante, int billetes[6], int cantidades[6], int cantBilletes, int usados[6], int &mejorCantBilletes, int mejorUsados[6])
{
    if (esSolucion(cambioRestante) && esMejorSolucion(cantBilletes, mejorCantBilletes))
    {
        clonarSolucion(usados, mejorUsados);
        mejorCantBilletes = cantBilletes;
    }
    else if (!hayQuePodar(cantBilletes, mejorCantBilletes))
    {
        // alternativas
        for (int i = 0; i < 6; i++)
        {
            if (esMovimientoValido(i, cambioRestante, billetes, cantidades))
            {
                aplicarMovimiento(i, cambioRestante, billetes, cantidades, cantBilletes, usados);
                cambioBT(cambioRestante, billetes, cantidades, cantBilletes, usados, mejorCantBilletes, mejorUsados);
                retirarMovimiento(i, cambioRestante, billetes, cantidades, cantBilletes, usados);
            }
        }
    }
}

int main()
{
    int billetes[6] = {5, 10, 20, 25, 50, 100};
    int cantidades[6] = {2, 3, 10, 8, 3, 2};
    int usadosPlayground[6] = {0, 0, 0, 0, 0, 0};
    int usados[6] = {0, 0, 0, 0, 0, 0};

    int billetesUsados = INF;
    int inf = INF;
    cambioBT(25, billetes, cantidades, 0, usadosPlayground, billetesUsados, usados);

    if (billetesUsados == inf)
    {
        cout << "No hay solucion" << endl;
    }
    else
    {
        cout << billetesUsados << endl;
        for (int i = 0; i < 6; i++)
        {
            if (usados[i] > 0)
            {
                cout << "Use el billete de " << billetes[i] << " " << usados[i] << " veces" << endl;
            }
        }
    }

    return 0;
}