#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

int combinatoria(int n, int k)
{
    // casos base
    if (k == 0 || k == n)
        return 1;
    return combinatoria(n - 1, k - 1) + combinatoria(n - 1, k);
}

int **initMatriz(int n, int k)
{
    int **matriz = new int *[n + 1]();
    for (int f = 0; f < n + 1; f++)
    {
        matriz[f] = new int[k + 1]();
        for (int c = 0; c < k + 1; c++)
        {
            matriz[f][c] = -1;
        }
    }
    return matriz;
}

int combinatoria_memo(int n, int k, int **memo)
{
    // casos base
    if (k == 0 || k == n)
        return 1;
    if (memo[n][k] != -1)
        return memo[n][k];
    memo[n][k] = combinatoria_memo(n - 1, k - 1, memo) + combinatoria_memo(n - 1, k, memo);
    return memo[n][k];
}

int combinatoria_tab(int n, int k)
{
    int ** tab = initMatriz(n, k);
    // casos base
    for(int i = 0 ; i <=n; i++) {
        tab[i][0] = 1;
    }
    for(int i = 0 ; i <= k; i++) {
        tab[i][i] = 1;
    }

    // "PR"
    for(int n_i = 1 ; n_i <= n; n_i++) {
        for(int k_i = 1 ; k_i < n_i; k_i++) {
            tab[n_i][k_i] = tab[n_i - 1][k_i - 1] + tab[n_i - 1][k_i];
        }
    }

    return tab[n][k];
}

void swap_arr(int* &a, int* &b) {
    int* c = a;
    a = b;
    b = c;
}

int combinatoria_tabv2(int n, int k)
{
    int n_curr = 0;
    int * curr = new int[n+1]();
    int * ant = new int[n+1]();

    for(int n_curr = 0; n_curr <= n; n_curr++) {
        swap_arr(curr, ant);
        for(int k_curr = 0; k_curr <= n_curr; k_curr++) {
            if(k_curr == 0 || n_curr == k_curr) {
                curr[k_curr] = 1;
            }else{
                curr[k_curr] = ant[k_curr] + ant[k_curr-1];
            }
        }
    }

    return curr[k];
}

int main()
{
    int n = 6;
    int k = 4;
    cout << combinatoria(n, k) << endl;
    int **memo = initMatriz(n, k);
    cout << combinatoria_memo(n, k, memo) << endl;
    cout << combinatoria_tab(n, k) << endl;
    cout << combinatoria_tabv2(n, k) << endl;

}