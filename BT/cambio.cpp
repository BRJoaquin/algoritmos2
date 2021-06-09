#include <cassert>
#include <string>
#include <iostream>
#include <limits.h>
using namespace std;

int const N = 5;
int valorMonedas[N] = {1, 2, 5, 10, 50};

bool esUnaMonedaValida(int objeto)
{
    return objeto < N;
}
bool puedoPonerLaMoneda(int moneda, int cambioADevolver)
{
    return cambioADevolver >= valorMonedas[moneda];
}
void colocarTentativamenteLaMoneda(int moneda, int &cambioADevolver, int &cantidadMonedasCandidatas)
{
    cambioADevolver -= valorMonedas[moneda];
    cantidadMonedasCandidatas++;
}
void retirarLaMoneda(int moneda, int &cambioADevolver, int &cantidadMonedasCandidatas)
{
    cambioADevolver += valorMonedas[moneda];
    cantidadMonedasCandidatas--;
}
bool esSolucion(int cambioADevolver)
{
    return cambioADevolver == 0; // termine de dar el cambio
}
bool esMejorSolucion(int cantidadMonedasCandidatas, int mejorCantidadMonedasCandidatas)
{
    return cantidadMonedasCandidatas < mejorCantidadMonedasCandidatas; // use menos monedas
}

void cambio(int moneda, int cambioADevolver, int cantidadMonedasCandidatas, int &mejorCantidadMonedasCandidatas)
{
    if (esUnaMonedaValida(moneda))
    {
        for (int alternativa = 0; alternativa <= 1; alternativa++)
        {
            bool pongoLaMoneda = alternativa == 0;
            // seria un movimiento valido para realizar
            if (pongoLaMoneda)
            {
                if (puedoPonerLaMoneda(moneda, cambioADevolver))
                {
                    // aplicamos el movimiento - usamos la moneda
                    colocarTentativamenteLaMoneda(moneda, cambioADevolver, cantidadMonedasCandidatas);

                    // si llegamos al destino, entontramos una solucion
                    if (esSolucion(cambioADevolver) && esMejorSolucion(cantidadMonedasCandidatas, mejorCantidadMonedasCandidatas))
                    {
                        mejorCantidadMonedasCandidatas = cantidadMonedasCandidatas;
                    }
                    // exploro el siguiente objeto
                    cambio(moneda + 1, cambioADevolver, cantidadMonedasCandidatas, mejorCantidadMonedasCandidatas);
                    // trato de volver a ponerlo
                    cambio(moneda, cambioADevolver, cantidadMonedasCandidatas, mejorCantidadMonedasCandidatas);

                    // deshacemos el movimiento
                    retirarLaMoneda(moneda, cambioADevolver, cantidadMonedasCandidatas);
                }
            }
            else
            {
                cambio(moneda + 1, cambioADevolver, cantidadMonedasCandidatas, mejorCantidadMonedasCandidatas);
            }
        }
    }
}

bool hayQuePodar(int candidato, int mejorSolucion)
{
    return candidato > mejorSolucion;
}

void cambioConPoda(int moneda, int cambioADevolver, int cantidadMonedasCandidatas, int &mejorCantidadMonedasCandidatas)
{
    if (!hayQuePodar(cantidadMonedasCandidatas, mejorCantidadMonedasCandidatas))
    {
        if (esUnaMonedaValida(moneda))
        {
            for (int alternativa = 0; alternativa <= 1; alternativa++)
            {
                bool pongoLaMoneda = alternativa == 0;
                // seria un movimiento valido para realizar
                if (pongoLaMoneda)
                {
                    if (puedoPonerLaMoneda(moneda, cambioADevolver))
                    {
                        // aplicamos el movimiento - usamos la moneda
                        colocarTentativamenteLaMoneda(moneda, cambioADevolver, cantidadMonedasCandidatas);

                        // si llegamos al destino, entontramos una solucion
                        if (esSolucion(cambioADevolver) && esMejorSolucion(cantidadMonedasCandidatas, mejorCantidadMonedasCandidatas))
                        {
                            mejorCantidadMonedasCandidatas = cantidadMonedasCandidatas;
                        }
                        // exploro el siguiente objeto
                        cambioConPoda(moneda + 1, cambioADevolver, cantidadMonedasCandidatas, mejorCantidadMonedasCandidatas);
                        // trato de volver a ponerlo
                        cambioConPoda(moneda, cambioADevolver, cantidadMonedasCandidatas, mejorCantidadMonedasCandidatas);

                        // deshacemos el movimiento
                        retirarLaMoneda(moneda, cambioADevolver, cantidadMonedasCandidatas);
                    }
                }
                else
                {
                    cambioConPoda(moneda + 1, cambioADevolver, cantidadMonedasCandidatas, mejorCantidadMonedasCandidatas);
                }
            }
        }
    }
}
void colocarTentativamenteLaMonedaCamino(int moneda, int &cambioADevolver, int &cantidadMonedasCandidatas, int solucionCandidata[N])
{
    cambioADevolver -= valorMonedas[moneda];
    solucionCandidata[moneda]++;
    cantidadMonedasCandidatas++;
}
void retirarLaMonedaCamino(int moneda, int &cambioADevolver, int &cantidadMonedasCandidatas, int solucionCandidata[N])
{
    cambioADevolver += valorMonedas[moneda];
    solucionCandidata[moneda]--;
    cantidadMonedasCandidatas--;
}
void clonarSolucion(int origen[N], int destino[N])
{
    for (int i = 0; i < N; i++)
    {
        destino[i] = origen[i];
    }
}
void cambioCamino(int moneda, int cambioADevolver, int cantidadMonedasCandidatas, int solucionCandidata[N], int &mejorCantidadMonedasCandidatas, int mejorSolucion[N])
{
    if (!hayQuePodar(cantidadMonedasCandidatas, mejorCantidadMonedasCandidatas))
    {
        if (esUnaMonedaValida(moneda))
        {
            for (int alternativa = 0; alternativa <= 1; alternativa++)
            {
                bool pongoLaMoneda = alternativa == 0;
                // seria un movimiento valido para realizar
                if (pongoLaMoneda)
                {
                    if (puedoPonerLaMoneda(moneda, cambioADevolver))
                    {
                        // aplicamos el movimiento - usamos la moneda
                        colocarTentativamenteLaMonedaCamino(moneda, cambioADevolver, cantidadMonedasCandidatas, solucionCandidata);

                        // si llegamos al destino, entontramos una solucion
                        if (esSolucion(cambioADevolver) && esMejorSolucion(cantidadMonedasCandidatas, mejorCantidadMonedasCandidatas))
                        {
                            mejorCantidadMonedasCandidatas = cantidadMonedasCandidatas;
                            clonarSolucion(solucionCandidata, mejorSolucion);
                        }
                        // exploro el siguiente objeto
                        cambioCamino(moneda + 1, cambioADevolver, cantidadMonedasCandidatas, solucionCandidata, mejorCantidadMonedasCandidatas, mejorSolucion);
                        // trato de volver a ponerlo
                        cambioCamino(moneda, cambioADevolver, cantidadMonedasCandidatas, solucionCandidata, mejorCantidadMonedasCandidatas, mejorSolucion);

                        // deshacemos el movimiento
                        retirarLaMonedaCamino(moneda, cambioADevolver, cantidadMonedasCandidatas, solucionCandidata);
                    }
                }
                else
                {
                    cambioCamino(moneda + 1, cambioADevolver, cantidadMonedasCandidatas, solucionCandidata, mejorCantidadMonedasCandidatas, mejorSolucion);
                }
            }
        }
    }
}

int main()
{
    // Caso 1
    // int cambioADevolver = 99;
    // int mejorSolucion = INT_MAX;
    // cambio(0, cambioADevolver, 0, mejorSolucion);
    // cout << "Se uso " << mejorSolucion << " monedas" << endl;

    // Caso 2
    // int cambioADevolver = 1000;
    // int mejorSolucion = INT_MAX;
    // cambio(0, cambioADevolver, 0, mejorSolucion);
    // cout << "Se uso " << mejorSolucion << " monedas" << endl;

    // Caso 3
    // int cambioADevolver = 1000;
    // int mejorSolucion = INT_MAX;
    // cambioConPoda(0, cambioADevolver, 0, mejorSolucion);
    // cout << "Se uso " << mejorSolucion << " monedas" << endl;

    // Caso 4
    int cambioADevolver = 99;
    int mejorSolucion = INT_MAX;
    int candidatoCamino[N] = {0, 0, 0, 0, 0};
    int mejorCamino[N] = {0, 0, 0, 0, 0};
    cambioCamino(0, cambioADevolver, 0, candidatoCamino, mejorSolucion, mejorCamino);
    cout << "Se uso " << mejorSolucion << " monedas" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "Use " << mejorCamino[i] << " monedas de " << valorMonedas[i] << endl;
    }
    
    // return 0;
}