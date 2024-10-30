#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;


int fiboRec(int n) {
    if(n<=1) return  n;
    return fiboRec(n-1) + fiboRec(n-2);
}

long fiboMemo(int n, long *memo) {
    if(n<=1) return  n;

    if(memo[n] == -1) {
        memo[n] = fiboMemo(n-1, memo) + fiboMemo(n-2, memo);
    }
    return memo[n];
}

long fiboTab(int n) {
    long *tab = new long[n+1]();
    // casos base
    tab[0] = 0;
    tab[1] = 1;
    // "caso recursivo"
    for (int i = 2; i <= n; i++)
    {
        tab[i] = tab[i-1] + tab[i-2];
    }
    return tab[n];
}


int main()
{
    int N = 61;

    // cout << fiboRec(N) << endl;

    long * memo = new long[N+1]();
    for (size_t i = 0; i < N+1; i++)
    {
        memo[i] = -1;
    }

    cout << fiboMemo(N, memo) << endl;
    cout << fiboTab(N) << endl;

    
  
}