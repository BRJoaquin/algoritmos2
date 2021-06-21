// Letra: https://www.geeksforgeeks.org/longest-possible-route-in-a-matrix-with-hurdles/
#include <string>
#include <iostream>
using namespace std;

bool sePuedePodar()
{
    return false;
}
bool esCoordenadaValida(int filaO, int colO, int filas, int columnas)
{
    return filaO < filas && filaO >= 0 && colO < columnas && colO >= 0;
}
bool puedoPasar(int filaO, int colO, int laberinto[3][10])
{
    return laberinto[filaO][colO] == 1;
}
bool esUnMovimientoValido(int filaO, int colO, int filas, int columnas, int laberinto[3][10])
{
    return esCoordenadaValida(filaO, colO, filas, columnas) && puedoPasar(filaO, colO, laberinto);
}
void aplicarMovimiento(int filaO, int colO, int laberinto[3][10], int paso)
{
    laberinto[filaO][colO] = paso + 2;
}
void quitoMovimiento(int filaO, int colO, int laberinto[3][10])
{
    laberinto[filaO][colO] = 1;
}

bool esSolucion(int filaO, int colO, int filaD, int colD)
{
    return filaO == filaD && colO == colD;
}
bool esMejorSolucion(int actual, int mejor)
{
    return actual > mejor;
}

void clonarLaSolucion(int origen[3][10], int destino[3][10])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            destino[i][j] = (origen[i][j] == 1 ? 0 : origen[i][j] - 1);
        }
    }
}

void caminoMasLargo(int filaO, int colO, int filaD, int colD, int laberinto[3][10], int filas, int columnas, int largoActual, int mejorSolucion[3][10], int &mejorMetrica)
{
    if (!sePuedePodar())
    {
        if (esUnMovimientoValido(filaO, colO, filas, columnas, laberinto))
        {
            aplicarMovimiento(filaO, colO, laberinto, largoActual);
            if (esSolucion(filaO, colO, filaD, colD) && esMejorSolucion(largoActual, mejorMetrica))
            {
                clonarLaSolucion(laberinto, mejorSolucion);
                mejorMetrica = largoActual;
            }
            else
            {
                // alternativas
                int dx[4] = {0, 1, -1, 0};
                int dy[4] = {-1, 0, 0, 1};
                for (int i = 0; i < 4; i++)
                {
                    caminoMasLargo(filaO + dx[i], colO + dy[i], filaD, colD, laberinto, filas, columnas, largoActual + 1, mejorSolucion, mejorMetrica);
                }
            }
            quitoMovimiento(filaO, colO, laberinto);
        }
    }
}

int main()
{
    int laberinto[3][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 0, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    int mejorSolucion[3][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    int mejorDeLosMejoresMejores = 0;
    caminoMasLargo(0, 0, 1, 7, laberinto, 3, 10, 0, mejorSolucion, mejorDeLosMejoresMejores);
    cout << mejorDeLosMejoresMejores << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << mejorSolucion[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}