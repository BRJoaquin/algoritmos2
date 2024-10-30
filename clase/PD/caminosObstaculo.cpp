#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int caminoMemotab(int N, int M, bool **obstaculos)
{
    int **tab = new int *[N + 1]();
    for (int i = 0; i < N + 1; i++)
    {
        tab[i] = new int[M + 1]();
    }

    tab[0][0] = 1;

    // casos base
    for (int i = 1; i < N + 1; i++)
    {
        tab[i][0] = obstaculos[i][0] ? 0 : tab[i - 1][0];
    }
    for (int i = 1; i < M + 1; i++)
    {
        tab[0][i] = obstaculos[0][i] ? 0 : tab[0][i - 1];
    }

    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < M + 1; j++)
        {
            tab[i][j] = obstaculos[i][j] ? 0 : tab[i - 1][j] + tab[i][j - 1];
        }
    }
    return tab[N][M];
}

int main()
{
    int N = 2;
    int M = 5;
    bool **obstaculos = new bool *[N + 1]();
    for (int i = 0; i < N + 1; i++)
    {
        obstaculos[i] = new bool[M + 1]();
    }
    obstaculos[0][2] = true;
    obstaculos[1][3] = true;
    obstaculos[1][4] = true;

    cout << caminoMemotab(N, M, obstaculos) << endl;
}