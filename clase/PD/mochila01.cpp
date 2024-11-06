#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

string nombres[4] = {"ruby", "lingote", "diamante", "moneda"};
int pesos[4] = {8, 5, 3, 4};
int valores[4] = {25, 10, 20, 8};

void mochila01(int n, int capacidad)
{
    int **tab = new int *[n + 1]();
    for (int i = 0; i <= n; i++)
    {
        tab[i] = new int[capacidad + 1]();
    }

    for (int objActual = 1; objActual <= n; objActual++)
    {
        int pesoObjeto = pesos[objActual - 1];
        int valorObjeto = valores[objActual - 1];
        for (int capacidadActual = 0; capacidadActual <= capacidad; capacidadActual++)
        {
            if (pesoObjeto > capacidadActual)
            {
                tab[objActual][capacidadActual] = tab[objActual - 1][capacidadActual];
            }
            else
            {
                int valorDeNoPonerObjeto = tab[objActual - 1][capacidadActual];
                int valoreDePonerObjeto = valorObjeto + tab[objActual - 1][capacidadActual - pesoObjeto];
                tab[objActual][capacidadActual] = valoreDePonerObjeto > valorDeNoPonerObjeto ? valoreDePonerObjeto : valorDeNoPonerObjeto;
            }
        }
    }

    cout << "El valor de la mochila es de " << tab[n][capacidad] << endl;

    int objetoActual = n;
    int capacidadActual = capacidad;
    while(objetoActual > 0) {
        bool useObjeto = tab[objetoActual][capacidadActual] != tab[objetoActual - 1][capacidadActual];
        if(useObjeto) {
            cout << "Use el objeto " << nombres[objetoActual - 1] << endl;
            capacidadActual -= pesos[objetoActual - 1];
        }
        objetoActual--;
    }

}

int main()
{
    mochila01(4, 13);
}