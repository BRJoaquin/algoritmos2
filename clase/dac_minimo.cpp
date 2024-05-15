#include <string>
#include <iostream>
#include <climits>
#include <cassert>

#define INF INT_MAX;

using namespace std;


int minimo(int* arr, int i, int f) {
    // problema trivial
    if(i==f) {
        // solucion trivial
        return arr[i];
    }

    // dividir
    int mitad = ((f - i) / 2) + i;

    // conquista
    int minIzq = minimo(arr, i, mitad);
    int minDer = minimo(arr, mitad + 1, f);

    // merge
    return minIzq < minDer ? minIzq : minDer;
}

int main()
{

    int* arr = new int[5]();
    arr[0] = 77;
    arr[1] = 7;
    arr[2] = 88;
    arr[3] = 2;
    arr[4] = 0;

    cout << minimo(arr, 0, 4) << endl;
}