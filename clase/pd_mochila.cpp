#include <string>
#include <iostream>
#include <climits>
#include <cassert>
#define INF INT_MAX;
using namespace std;


int CAPACIDAD_PESO = 13;

int   valores[4] = { 10, 20, 25, 8};
int     pesos[4] = { 5,   3,  8, 4};
string nombres[4] = {"lingote", "diamante", "ruby", "moneda"};


int mochila01(int objetoHasta, int capacidad) {
    // si yo no tengo objetos o me quede sin capacidad
    if(objetoHasta < 0 || capacidad == 0) {
        return 0;
    }
    // si a mi no me entra el opbjeto lo ignoro
    if(capacidad < pesos[objetoHasta]) {
        return mochila01(objetoHasta-1, capacidad);
    }

    int valorDePonerElObjeto = valores[objetoHasta] + mochila01(objetoHasta - 1, capacidad - pesos[objetoHasta]);
    int valorDeNOPonerElObjeto = mochila01(objetoHasta - 1, capacidad);

    return max(valorDePonerElObjeto, valorDeNOPonerElObjeto);
}

void imprimirMatriz(int** m, int f, int c) {
    for (int i = 0; i < f; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int** initMatriz(int objetoHasta, int capacidad){
    int **matriz = new int *[objetoHasta + 2]();
    for (int f = 0; f < objetoHasta + 2; f++)
    {
        matriz[f] = new int[capacidad + 1]();
    }
    return matriz;
}

int mochila01_tab(int objetoHasta, int capacidad) {
    int** tab = initMatriz(objetoHasta, capacidad);

    // no tengo ningun objeto
    for (int capActual = 0; capActual <= capacidad; capActual++)
    {
        tab[0][capActual] = 0;
    }

    // no tengo ningun objeto
    for (int objetoActual = 1; objetoActual <= objetoHasta + 1; objetoActual++)
    {
        int valorObjetoHasta = valores[objetoActual - 1];
        int pesoObjetoHasta = pesos[objetoActual - 1];
        for (int capActual = 0; capActual <= capacidad; capActual++)
        {
            if(capActual < pesoObjetoHasta) {
                tab[objetoActual][capActual] = tab[objetoActual - 1][capActual];
            } else {
                int valorPonerObjeto = valorObjetoHasta + tab[objetoActual - 1][capActual - pesoObjetoHasta];
                int valorNoPonerObjeto = tab[objetoActual - 1][capActual];
                tab[objetoActual][capActual] = valorPonerObjeto > valorNoPonerObjeto ? valorPonerObjeto : valorNoPonerObjeto;
            }
        }
    }

    // imprimirMatriz(tab, objetoHasta + 2, capacidad + 1);

    int objetoIndex = objetoHasta + 1;
    int capacidadIndex = capacidad;

    while(objetoIndex > 0) {
        bool useElObjeto = tab[objetoIndex][capacidadIndex] != tab[objetoIndex - 1][capacidadIndex];
        if(useElObjeto) {
            cout << "Use el objeto " << nombres[objetoIndex-1] << endl;
            capacidadIndex-= pesos[objetoIndex-1];
        }
        objetoIndex--;
    }


    return tab[objetoHasta + 1][capacidad];
}



int mochila0Inf(int objetoHasta, int capacidad) {
    // si yo no tengo objetos o me quede sin capacidad
    if(objetoHasta < 0 || capacidad == 0) {
        return 0;
    }
    // si a mi no me entra el opbjeto lo ignoro
    if(capacidad < pesos[objetoHasta]) {
        return mochila0Inf(objetoHasta-1, capacidad);
    }

    int valorDePonerElObjeto = valores[objetoHasta] + mochila0Inf(objetoHasta, capacidad - pesos[objetoHasta]);
    int valorDeNOPonerElObjeto = mochila0Inf(objetoHasta - 1, capacidad);

    return max(valorDePonerElObjeto, valorDeNOPonerElObjeto);
}


int mochila0Inf_tab(int objetoHasta, int capacidad) {
    int** tab = initMatriz(objetoHasta, capacidad);

    // no tengo ningun objeto
    for (int capActual = 0; capActual <= capacidad; capActual++)
    {
        tab[0][capActual] = 0;
    }

    // no tengo ningun objeto
    for (int objetoActual = 1; objetoActual <= objetoHasta + 1; objetoActual++)
    {
        int valorObjetoHasta = valores[objetoActual - 1];
        int pesoObjetoHasta = pesos[objetoActual - 1];
        for (int capActual = 0; capActual <= capacidad; capActual++)
        {
            if(capActual < pesoObjetoHasta) {
                tab[objetoActual][capActual] = tab[objetoActual - 1][capActual];
            } else {
                int valorPonerObjeto = valorObjetoHasta + tab[objetoActual][capActual - pesoObjetoHasta];
                int valorNoPonerObjeto = tab[objetoActual - 1][capActual];
                tab[objetoActual][capActual] = valorPonerObjeto > valorNoPonerObjeto ? valorPonerObjeto : valorNoPonerObjeto;
            }
        }
    }

    int objetoIndex = objetoHasta + 1;
    int capacidadIndex = capacidad;

    while(objetoIndex > 0) {
        bool useElObjeto = tab[objetoIndex][capacidadIndex] != tab[objetoIndex - 1][capacidadIndex];
        if(useElObjeto) {
            cout << "Use el objeto " << nombres[objetoIndex-1] << endl;
            capacidadIndex-= pesos[objetoIndex-1];
        }else {
            objetoIndex--;
        }
    }


    return tab[objetoHasta + 1][capacidad];
}

int CAPACIDAD_VOLUMEN = 4;
int vol[4] = { 5, 2, 2, 2 };

int*** initMatrizMulti(int objetoHasta, int capacidadPeso, int capacidadVol){
    int ***matriz = new int **[objetoHasta + 2]();
    for (int f = 0; f < objetoHasta + 2; f++)
    {
        matriz[f] = new int*[capacidadPeso + 1]();
        for (int c = 0; c < capacidadPeso + 1; c++)
        {
            matriz[f][c] = new int[capacidadVol + 1]();
        }
        
    }
    return matriz;
}

int mochila01Multi_tab(int objetoHasta, int capacidadPeso, int capacidadVol) {
    int*** tab = initMatrizMulti(objetoHasta, capacidadPeso, capacidadVol);

    // no tengo ningun objeto
    for (int capPesoActual = 0; capPesoActual <= capacidadPeso; capPesoActual++)
    {
        for (int capVolActual = 0; capVolActual <= capacidadVol; capVolActual++)
        {
            tab[0][capPesoActual][capVolActual] = 0;
        }
    }

    // no tengo ningun objeto
    for (int objetoActual = 1; objetoActual <= objetoHasta + 1; objetoActual++)
    {
        int valorObjetoHasta = valores[objetoActual - 1];
        int pesoObjetoHasta = pesos[objetoActual - 1];
        int volObjetoHasta = vol[objetoActual - 1];
        for (int capPesoActual = 0; capPesoActual <= capacidadPeso; capPesoActual++)
        {
            for (int capVolActual = 0; capVolActual <= capacidadVol; capVolActual++)
            {
                if(capPesoActual < pesoObjetoHasta || capVolActual < volObjetoHasta) {
                    tab[objetoActual][capPesoActual][capVolActual] = tab[objetoActual - 1][capPesoActual][capVolActual];
                } else {
                    int valorPonerObjeto = valorObjetoHasta + tab[objetoActual - 1][capPesoActual - pesoObjetoHasta][capVolActual - volObjetoHasta];
                    int valorNoPonerObjeto = tab[objetoActual - 1][capPesoActual][capVolActual];
                    tab[objetoActual][capPesoActual][capVolActual] = valorPonerObjeto > valorNoPonerObjeto ? valorPonerObjeto : valorNoPonerObjeto;
                }
            }
        }
    }

    // imprimirMatriz(tab, objetoHasta + 2, capacidad + 1);

    // int objetoIndex = objetoHasta + 1;
    // int capacidadIndex = capacidadPeso;

    // while(objetoIndex > 0) {
    //     bool useElObjeto = tab[objetoIndex][capacidadIndex] != tab[objetoIndex - 1][capacidadIndex];
    //     if(useElObjeto) {
    //         cout << "Use el objeto " << nombres[objetoIndex-1] << endl;
    //         capacidadIndex-= pesos[objetoIndex-1];
    //     }
    //     objetoIndex--;
    // }


    return tab[objetoHasta + 1][capacidadPeso][capacidadVol];
}


int main()
{
    cout << "Mochila 01 DAC:" << endl;
    cout << mochila01(3, CAPACIDAD_PESO) << endl;

    cout << "Mochila 01 PD (TAB):" << endl;
    cout << mochila01_tab(3, CAPACIDAD_PESO) << endl;

    cout << "Mochila 0Inf DAC:" << endl;
    cout << mochila0Inf(3, CAPACIDAD_PESO) << endl;

    cout << "Mochila 0Inf PD (TAB):" << endl;
    cout << mochila0Inf_tab(3, CAPACIDAD_PESO) << endl;

    cout << "Mochila 01 PD Multi (TAB):" << endl;
    cout << mochila01Multi_tab(3, CAPACIDAD_PESO, CAPACIDAD_VOLUMEN) << endl;
}