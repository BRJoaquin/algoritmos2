#include <string>
#include <iostream>
#include <climits>
#include <cassert>

#define INF INT_MAX;

using namespace std;


bool existe(int* arr, int i, int f, int buscado) {
    // caso base
    if(i == f) {
        return arr[i] == buscado;
    }

    // dividir
    int mitad = ((f - i) / 2) + i;

    // conquista
    bool estaIzq =  existe(arr, i, mitad, buscado);
    bool estaDer = existe(arr, mitad + 1, f, buscado);
    // merge
    return estaIzq || estaDer;
}

bool existev2(int* arr, int i, int f, int buscado) {
    // caso base
    if(i == f) {
        return arr[i] == buscado;
    }

    // dividir
    int mitad = ((f - i) / 2) + i;

    if(arr[mitad] >= buscado) {
        return existev2(arr, i, mitad, buscado);
    } else {
        return existev2(arr, mitad + 1, f, buscado);
    }
}




// [4, 7, 88, 334, 1009]
int main()
{

    int* arr = new int[5]();
    arr[0] = 4;
    arr[1] = 7;
    arr[2] = 88;
    arr[3] = 334;
    arr[4] = 1009;

    if(existev2(arr, 0, 4, 88)) {
        cout << "existe" << endl;
    }else {
        cout << "no existe" << endl; 
    }
}