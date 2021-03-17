#ifndef TABLA_HASH_ABIERTA
#define TABLA_HASH_ABIERTA
#include <string>
#include <iostream>
using namespace std;

struct NodoLista
{
    string clave;
    int valor;
    NodoLista *sig;
    NodoLista(string unaClave, int unValor) : clave(unaClave), valor(unValor), sig(0){};
    NodoLista(string unaClave, int unValor, NodoLista *unSig) : clave(unaClave), valor(unValor), sig(unSig){};
};

class TablaHashAbierta_Agenda
{
private:
    typedef NodoLista *Lista;
    Lista *arrList;
    int tamanio;
    int cantidadDeElementos;

    void rehash()
    {
        int nuevoTamanio = this->tamanio * 2;
        Lista *nuevoArray = new Lista[nuevoTamanio];
        Lista *viejoArray = this->arrList;
        // recorrer todos los elementos de mi viejo array
        for (int i = 0; i < this->tamanio; i++)
        {
            Lista nodoLista = arrList[i];
            while (nodoLista != NULL)
            {
                int pos = abs(this->fnHash(nodoLista->clave)) % nuevoTamanio;
                Lista bucket = nuevoArray[pos];
                Lista nuevoNodo = new NodoLista(nodoLista->clave, nodoLista->valor, bucket);
                nuevoArray[pos] = nuevoNodo;

                nodoLista = nodoLista->sig;
            }
        }
        this->tamanio = nuevoTamanio;
        this->arrList = nuevoArray;
        // TODO delete viejoArray
    }

    float factorDeCarga()
    {
        return (float)this->cantidadDeElementos / this->tamanio;
    }

    bool insertarRecusrivo(string unaClave, int unValor, NodoLista *&ptr)
    {
        if (ptr == NULL)
        {
            ptr = new NodoLista(unaClave, unValor);
            return false;
        }
        else
        {
            if (ptr->clave == unaClave)
            {
                ptr->valor = unValor;
                return true;
            }
            else
            {
                return insertarRecusrivo(unaClave, unValor, ptr->sig);
            }
        }
    }

public:
    TablaHashAbierta_Agenda(int tamaniInicial)
    {
        this->tamanio = tamaniInicial;
        this->cantidadDeElementos = 0;
        arrList = new Lista[this->tamanio];
    }

    int fnHash(string clave)
    {
        int sum = 0;
        for (int k = 0; k < clave.length(); k++)
            sum = sum + int(clave[k]);
        return sum;
        // return clave[0] - 65;
    }

    void insertar(string unaClave, int unValor)
    {
        // Insertar siempre al pricipio
        // int pos = abs(this->fnHash(unaClave)) % this->tamanio;
        // Lista bucket = this->arrList[pos];
        // Lista nuevoNodo = new NodoLista(unaClave, unValor, bucket);
        // this->arrList[pos] = nuevoNodo;
        // this->cantidadDeElementos++;

        int pos = abs(this->fnHash(unaClave)) % this->tamanio;
        if (!this->insertarRecusrivo(unaClave, unValor, arrList[pos]))
        {
            this->cantidadDeElementos++;
        }

        if (this->factorDeCarga() > 0.7)
        {
            this->rehash();
        }
    }

    void imprimir()
    {
        for (int i = 0; i < this->tamanio; i++)
        {
            cout << "[ ] ->";
            Lista nodoLista = arrList[i];
            while (nodoLista != NULL)
            {
                cout << " " << nodoLista->clave << "/" << nodoLista->valor << " ->";
                nodoLista = nodoLista->sig;
            }
            cout << " nl" << endl;
        }
    }
};

int main()
{
    int opc = -1;
    TablaHashAbierta_Agenda *tabla = new TablaHashAbierta_Agenda(10);
    while (opc != 0)
    {
        cout << "Seleccione operacion:" << endl;
        cout << "0) Salir" << endl;
        cout << "1) Ingresar dato" << endl;
        cout << "2) Imprimir tabla" << endl;
        cout << "3) Generar datos de entrada" << endl;
        // cout << "4) Rehash" << endl;

        cin >> opc;
        if (opc == 1)
        {
            string nombre;
            int telefono;
            cout << "Ingrese nombre" << endl;
            cin >> nombre;
            cout << "Ingrese telefono" << endl;
            cin >> telefono;
            tabla->insertar(nombre, telefono);
        }
        else if (opc == 2)
        {
            tabla->imprimir();
        }
        else if (opc == 3)
        {
            int cantidadDeDatos;
            cout << "Ingrese la cantidad de datos a ingresar" << endl;
            cin >> cantidadDeDatos;
            for (int i = 0; i < cantidadDeDatos; i++)
            {
                string nombreRandom = "";
                for (int j = 0; j < 3; j++)
                {
                    nombreRandom += (char)(rand() % 26 + 65);
                }
                int numeroRandom = rand() % 900 + 100;
                tabla->insertar(nombreRandom, numeroRandom);
            }
        }
    }

    return 0;
}

#endif