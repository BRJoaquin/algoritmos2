#include <cassert>
#include <string>
#include <iostream>
using namespace std;

int mochila01(int capacidad, int cantidadObjetos, int pesos[], int valores[])
{
    int **m = new int *[cantidadObjetos + 1];
    for (int i = 0; i < cantidadObjetos + 1; i++)
    {
        m[i] = new int[capacidad+1]();
    }

    for (int objetoHasta = 1; objetoHasta < cantidadObjetos+1; objetoHasta++)
    {
        for (int capacidadHasta = 0; capacidadHasta < capacidad+1; capacidadHasta++)
        {
            if(pesos[objetoHasta-1] > capacidadHasta) {
                m[objetoHasta][capacidadHasta] = m[objetoHasta-1][capacidadHasta];
            }else{
                int valorMochilaDePonerlo = valores[objetoHasta-1] + m[objetoHasta-1][capacidadHasta - pesos[objetoHasta-1]];
                int valorMochilaDeNOPonerlo =  m[objetoHasta-1][capacidadHasta];
                m[objetoHasta][capacidadHasta] =  valorMochilaDePonerlo > valorMochilaDeNOPonerlo ? valorMochilaDePonerlo : valorMochilaDeNOPonerlo;
            }
        }
    }
    
    return m[cantidadObjetos][capacidad];
}

void mochila01Recorrido(int capacidad, int cantidadObjetos, int pesos[], int valores[])
{
    int **m = new int *[cantidadObjetos + 1];
    for (int i = 0; i < cantidadObjetos + 1; i++)
    {
        m[i] = new int[capacidad+1]();
    }

    for (int objetoHasta = 1; objetoHasta < cantidadObjetos+1; objetoHasta++)
    {
        for (int capacidadHasta = 0; capacidadHasta < capacidad+1; capacidadHasta++)
        {
            if(pesos[objetoHasta-1] > capacidadHasta) {
                m[objetoHasta][capacidadHasta] = m[objetoHasta-1][capacidadHasta];
            }else{
                int valorMochilaDePonerlo = valores[objetoHasta-1] + m[objetoHasta-1][capacidadHasta - pesos[objetoHasta-1]];
                int valorMochilaDeNOPonerlo =  m[objetoHasta-1][capacidadHasta];
                m[objetoHasta][capacidadHasta] =  valorMochilaDePonerlo > valorMochilaDeNOPonerlo ? valorMochilaDePonerlo : valorMochilaDeNOPonerlo;
            }
        }
    }
    
    cout << "Valor de la mochila: " << m[cantidadObjetos][capacidad] << endl;
    cout << "Objetos usados:" << endl;
    int objetoIndex = cantidadObjetos;
    int capacidadIndex = capacidad;
    while(objetoIndex > 0) {
        if(m[objetoIndex][capacidadIndex] != m[objetoIndex - 1][capacidadIndex]) { // use el objeto
            cout << "Use el objeto " << objetoIndex << " p:" << pesos[objetoIndex - 1] << " v:" << valores[objetoIndex - 1] << endl;
            capacidadIndex -= pesos[objetoIndex - 1];
        }
        objetoIndex--;
    }

}


void mochilaINFRecorrido(int capacidad, int cantidadObjetos, int pesos[], int valores[])
{
    int **m = new int *[cantidadObjetos + 1];
    for (int i = 0; i < cantidadObjetos + 1; i++)
    {
        m[i] = new int[capacidad+1]();
    }

    for (int objetoHasta = 1; objetoHasta < cantidadObjetos+1; objetoHasta++)
    {
        for (int capacidadHasta = 0; capacidadHasta < capacidad+1; capacidadHasta++)
        {
            if(pesos[objetoHasta-1] > capacidadHasta) {
                m[objetoHasta][capacidadHasta] = m[objetoHasta-1][capacidadHasta];
            }else{
                int valorMochilaDePonerlo = valores[objetoHasta-1] + m[objetoHasta][capacidadHasta - pesos[objetoHasta-1]];
                int valorMochilaDeNOPonerlo =  m[objetoHasta-1][capacidadHasta];
                m[objetoHasta][capacidadHasta] =  valorMochilaDePonerlo > valorMochilaDeNOPonerlo ? valorMochilaDePonerlo : valorMochilaDeNOPonerlo;
            }
        }
    }
    
    cout << "Valor de la mochila: " << m[cantidadObjetos][capacidad] << endl;
    cout << "Objetos usados:" << endl;
    int objetoIndex = cantidadObjetos;
    int capacidadIndex = capacidad;
    while(objetoIndex > 0) {
        if(m[objetoIndex][capacidadIndex] != m[objetoIndex - 1][capacidadIndex]) { // use el objeto
            cout << "Use el objeto " << objetoIndex << " p:" << pesos[objetoIndex - 1] << " v:" << valores[objetoIndex - 1] << endl;
            capacidadIndex -= pesos[objetoIndex - 1];
        } else {
            objetoIndex--;
        }
    }

}

int main()
{
    // caso 1
    // int cantidadObjetos = 4;
    // int pesos[cantidadObjetos] = {5, 3, 8, 4};
    // int valores[cantidadObjetos] = {10, 20, 25, 8};
    // int capacidadMochila = 12;

    // caso 2
    // int cantidadObjetos = 4;
    // int pesos[cantidadObjetos] = {24, 10, 10, 7};
    // int valores[cantidadObjetos] = {24, 18, 18, 10};
    // int capacidadMochila = 25;

    // caso 3
    // int cantidadObjetos = 3;
    // int pesos[cantidadObjetos] = {10, 40, 20};
    // int valores[cantidadObjetos] = {100, 280, 120};
    // int capacidadMochila = 60;

    // caso 4
    // int cantidadObjetos = 4;
    // int pesos[cantidadObjetos] = {2, 10, 20, 50};
    // int valores[cantidadObjetos] = {1, 11, 22, 60};
    // int capacidadMochila = 88;

    

    // cout << mochila01(capacidadMochila, cantidadObjetos, pesos, valores) << endl;
    // mochila01Recorrido(capacidadMochila, cantidadObjetos, pesos, valores) ;
    // mochilaINFRecorrido(capacidadMochila, cantidadObjetos, pesos, valores) ;
    return 0;
}