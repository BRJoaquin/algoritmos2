#include <cassert>
#include <string>
#include <iostream>
using namespace std;

/*
f(0) = 1
f(1) = 1
f(2) = 2

f(n) = f(n-1) + f(n-2)
*/

int fiboRec(int n)
{
    if (n <= 1)
        return n;
    return fiboRec(n - 1) + fiboRec(n - 2);
}

int fiboBottomUP(int n)
{
    int *res = new int[n + 1];
    res[0] = 0;
    res[1] = 1;
    for (int i = 2; i <= n; i++)
        res[i] = res[i - 1] + res[i - 2];
    return res[n];
}

// Nos podemos ahorrar el array
int fiboBottomUPV2(int n)
{
    int antAnt = 0;
    int ant = 1;
    int ret;
    for (int i = 2; i <= n; i++) {
        ret = ant + antAnt;
        antAnt = ant;
        ant = ret;
    }
    return ret;
}

int fiboTopDownAux(int n, int *res)
{
    if (n <= 1)
        return n;
    if (res[n] == 0) {
        res[n] = fiboTopDownAux(n - 1, res) 
                + fiboTopDownAux(n - 2, res);
    }
    return res[n];
}

int fiboTopDown(int n)
{
    int *res = new int[n + 1]();
    return fiboTopDownAux(n, res);
}

int main()
{
    int N;
    cin >> N;
    cout << "Fibonacci Recursivo: " << fiboRec(N) << endl;
    cout << "Fibonacci PM Tabulation (bottom-up): " << fiboBottomUP(N) << endl;
    cout << "Fibonacci PM Tabulation (bottom-up) v2: " << fiboBottomUPV2(N) << endl;
    cout << "Fibonacci PM Memoization (top-down): " << fiboTopDown(N) << endl;
    return 0;
}