#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

bool llegueADestino(int fAc, int cAc, int fD, int cD)
{
    return fAc == fD && cAc == cD;
}

int caminoMenosParedes(int laberinto[5][10], int fO, int fD)
{
    int fAc = fO;
    int cAc = 0;
    int cD = 9;

    int movVertical = fD < fO ? -1 : 1;
    int paredesRotas = 0;

    while (!llegueADestino(fAc, cAc, fD, cD))
    {
        if (laberinto[fAc][cAc] == 1)
        {
            paredesRotas++;
        }

        // a donde nos movemos?

        if (fAc == fD)
        {
            // solo puedo ir a la derecha
            cAc++;
        }
        else if (cAc == cD)
        {
            // solo puedo ir hacia abajo
            fAc += movVertical;
        }
        else if (laberinto[fAc][cAc + 1] == 0 && laberinto[fAc + movVertical][cAc] == 1)
        {
            // si tenemos un 0 a la derecha y 1 hacia la direccion vertical vamos a la derecha
            cAc++;
        }
        else if (laberinto[fAc][cAc + 1] == 1 && laberinto[fAc + movVertical][cAc] == 0)
        {
            // si tenemos un 1 a la derecha y 0 hacia el mov veritical, vamos al mov vertical
            fAc += movVertical;
        }
        else
        {
            int df = abs(fD - fAc);
            int dc = abs(cD - cAc);
            if (df > dc)
            {
                fAc += movVertical;
            }
            else
            {
                cAc++;
            }
        }
    }
    return paredesRotas;
}

int main()
{
    int laberinto[5][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 1, 0, 1, 0, 0, 1},
        {0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0}};

    cout << caminoMenosParedes(laberinto, 2, 4) << endl; 
}