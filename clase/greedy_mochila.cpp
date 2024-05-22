#include <string>
#include <iostream>
#include <climits>
#include <cassert>
#include <algorithm>

using namespace std;

struct Objeto {
    string nombre;
    int valor;
    int peso;
};

int CANT_OBJ = 4;

bool comparadorValor(const Objeto &o1, const Objeto &o2) {
    return o1.valor > o2.valor;
}

bool comparadorPeso(const Objeto &o1, const Objeto &o2) {
    return o1.peso < o2.peso;
}

bool comparadorRatio(const Objeto &o1, const Objeto &o2) {
    float r1 =  (float)(o1.valor/o1.peso);
    float r2 =  (float)(o2.valor/o2.peso);

    return r1 > r2;
}

void mochila(int capacidad, Objeto* objetos) {
    std::sort(objetos, objetos + CANT_OBJ, comparadorRatio);
    for (int i = 0; i < CANT_OBJ; i++)
    {
        Objeto objeto = objetos[i];
        if(capacidad >= objeto.peso) {
            cout << objeto.nombre << " v:" << objeto.valor << " p:" << objeto.peso << endl;
            capacidad -= objeto.peso;
        }
    }
}

int main()
{
    Objeto objetos[CANT_OBJ] = {
        {"Ruby",     25, 8},
        {"Diamante", 20, 3},
        {"Oro",      10, 5},
        {"Moneda",    8, 4}
    };
    int capacidad =  13;
    mochila(capacidad, objetos);
}