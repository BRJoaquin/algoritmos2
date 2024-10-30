#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int caminioRec(int N, int M)
{
    if (N == 0 || M == 0)
    {
        return 1;
    }
    return caminioRec(N - 1, M) + caminioRec(N, M - 1);
}

int caminoMemo(int N, int M, int **memo)
{
    if (N == 0 || M == 0)
    {
        return 1;
    }
    if (memo[N][M] == 0)
    {
        memo[N][M] = caminioRec(N - 1, M) + caminioRec(N, M - 1);
    }
    return memo[N][M];
}

int caminoMemoAux(int N, int M)
{
    int **memo = new int *[N + 1]();
    for (int i = 0; i < N + 1; i++)
    {
        memo[i] = new int[M + 1]();
    }
    return caminoMemo(N, M, memo);
}

int caminoMemotab(int N, int M)
{
    int **tab = new int *[N + 1]();
    for (int i = 0; i < N + 1; i++)
    {
        tab[i] = new int[M + 1]();
    }

    // casos base
    for (int i = 0; i < N + 1; i++)
    {
        tab[i][0] = 1;
    }
    for (int i = 0; i < M + 1; i++)
    {
        tab[0][i] = 1;
    }

    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 1; j < M + 1; j++)
        {
            tab[i][j] = tab[i - 1][j] + tab[i][j - 1];
        }
    }
    return tab[N][M];
}

int main()
{
    cout << caminioRec(2, 5) << endl;
    cout << caminoMemoAux(2, 5) << endl;
    cout << caminoMemotab(2, 5) << endl;

}