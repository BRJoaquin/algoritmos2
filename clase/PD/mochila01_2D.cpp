#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

string nombres[4] = {"ruby", "lingote", "diamante", "moneda"};
int pesos[4] = {8, 5, 3, 4};
int valores[4] = {25, 10, 20, 8};
int volumenes[4] = {1, 3, 1, 2};

void mochila01_2d(int n, int capacidadPeso, int capacidadVolumen)
{
    int ***tab = new int **[n + 1]();
    for (int i = 0; i <= n; i++)
    {
        tab[i] = new int*[capacidadPeso + 1]();
        for (int j = 0; j <= capacidadPeso; j++)
        {
            tab[i][j] = new int[capacidadVolumen + 1]();
        }
    }

    for (int objActual = 1; objActual <= n; objActual++)
    {
        int pesoObjeto = pesos[objActual - 1];
        int volObjeto = volumenes[objActual - 1];
        int valorObjeto = valores[objActual - 1];

        for (int capPesoAct = 0; capPesoAct <= capacidadPeso; capPesoAct++)
        {
            for (int capVolAct = 0; capVolAct <= capacidadVolumen; capVolAct++)
            {
                if (pesoObjeto > capPesoAct || volObjeto > capVolAct)
                {
                    tab[objActual][capPesoAct][capVolAct] = tab[objActual - 1][capPesoAct][capVolAct];
                }
                else
                {
                    int valorDeNoPonerObjeto = tab[objActual - 1][capPesoAct][capVolAct];
                    int valoreDePonerObjeto = valorObjeto + tab[objActual - 1][capPesoAct - pesoObjeto][capVolAct - volObjeto];
                    tab[objActual][capPesoAct][capVolAct] = valoreDePonerObjeto > valorDeNoPonerObjeto ? valoreDePonerObjeto : valorDeNoPonerObjeto;
                }
            }
        }
    }

    cout << "El valor de la mochila es de " << tab[n][capacidadPeso][capacidadVolumen] << endl;

    int objetoActual = n;
    int capPesoAct = capacidadPeso;
    int capVolAct =  capacidadVolumen;
    while(objetoActual > 0) {
        bool useObjeto = tab[objetoActual][capPesoAct][capVolAct] != tab[objetoActual - 1][capPesoAct][capVolAct];
        if(useObjeto) {
            cout << "Use el objeto " << nombres[objetoActual - 1] << endl;
            capPesoAct -= pesos[objetoActual - 1];
            capVolAct  -= volumenes[objetoActual -1];
        }
        objetoActual--;
    }
}

int main()
{
    mochila01_2d(4, 40, 4);
}