#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

int N = 4;

bool esSolucion(int colAct)
{
    return colAct == N;
}

void colocarLaReina(int f, int c, bool **reinas)
{
    reinas[f][c] = true;
}

void quitarLaReina(int f, int c, bool **reinas)
{
    reinas[f][c] = false;
}

bool posValida(int f, int c)
{
    return f < N && c < N && c >= 0 && f >= 0;
}

bool puedoColocarReina(int fTen, int cTen, bool **reinas)
{

    // chequear hacia atras
    for (int c = cTen, f = fTen; posValida(f, c); c--)
    {
        if (reinas[f][c])
        {
            return false;
        }
    }

    //
    for (int c = cTen, f = fTen; posValida(f, c); c--, f--)
    {
        if (reinas[f][c])
        {
            return false;
        }
    }

    //
    for (int c = cTen, f = fTen; posValida(f, c); c--, f++)
    {
        if (reinas[f][c])
        {
            return false;
        }
    }

    return true;
}

void nReinas(int colAct, bool **reinas)
{
    if (esSolucion(colAct))
    {
        cout << "encontre una solucion!" << endl;
    }
    else
    {
        // movimientos posibles
        for (int f = 0; f < N; f++)
        {
            // if podemosAplicarMovimiento
            if (puedoColocarReina(f, colAct, reinas))
            {
                // aplicamos movimiento
                colocarLaReina(f, colAct, reinas);
                // llamo recursivamente
                nReinas(colAct + 1, reinas);
                // deshacer movimiento
                quitarLaReina(f, colAct, reinas);
            }
        }
    }
}

int main()
{
    bool **reinas = new bool *[N];
    for (int i = 0; i < N; i++)
    {
        reinas[i] = new bool[N]();
    }

    nReinas(0, reinas);
}