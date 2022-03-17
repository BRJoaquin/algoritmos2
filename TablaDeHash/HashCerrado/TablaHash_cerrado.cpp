#ifndef TABLA_HASH_CERRADO
#define TABLA_HASH_CERRADO
#include <string>
#include <iostream>
#include <math.h>
using namespace std;

struct Asociacion
{
    string clave;
    int valor;
    Asociacion(string unaClave, int unValor) : clave(unaClave), valor(unValor){};
};

class TablaHashCerrada_Agenda
{
private:
    Asociacion **array;
    int tamanio;
    int cantidadDeElementos;

    bool esPrimo(int n)
    {
        if (n <= 1)
            return false;
        if (n <= 3)
            return true;
        if (n % 2 == 0 || n % 3 == 0)
            return false;
        for (int i = 5; i * i <= n; i = i + 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        return true;
    }

    int siguientePrimo(int N)
    {
        // https://www.geeksforgeeks.org/program-to-find-the-next-prime-number/
        if (N <= 1)
            return 2;
        int prime = N;
        bool found = false;
        while (!found)
        {
            prime++;
            if (esPrimo(prime))
                found = true;
        }
        return prime;
    }

    float factorDeCarga()
    {
        return (float)this->cantidadDeElementos / this->tamanio;
    }

    int fnHash(string clave)
    {
        int sum = 0;
        for (int k = 0; k < clave.length(); k++)
            sum = sum + int(clave[k]);
        return sum;
    }

    // solo para doble hash
    int fnHash2(string clave)
    {
        return clave.length();
    }

    void rehash()
    {
        int nuevoTamanio = this->siguientePrimo(this->tamanio * 2);
        Asociacion **nuevoArray = new Asociacion *[nuevoTamanio]();

        for (int i = 0; i < this->tamanio; i++)
        {
            Asociacion *aux = array[i];
            if (aux != NULL)
            {
                this->insertar(nuevoArray, nuevoTamanio, aux->clave, aux->valor);
            }
        }
        this->array = nuevoArray;
        this->tamanio = nuevoTamanio;
        // TODO delete anterior
    }

    void insertar(Asociacion **arr, int arrSize, string unaClave, int unValor)
    {
        int hashValue = this->fnHash(unaClave);
        int pos = hashValue % arrSize;
        int i = 1;
        int inserte = false;
        int hashValue2 = this->fnHash2(unaClave);

        while (!inserte)
        {
            if (arr[pos] == NULL)
            {
                arr[pos] = new Asociacion(unaClave, unValor);
                this->cantidadDeElementos++;
                inserte = true;
            }
            else if (arr[pos]->clave.compare(unaClave) == 0)
            {
                arr[pos]->valor = unValor;
                inserte = true;
            }
            // Lineal
            // pos = (hashValue + i) % arrSize;

            // // Cuadratico
            // pos = (int)(hashValue + pow(i, 2)) % arrSize;

            // Doble Hash
            pos = (int)(hashValue + i*hashValue2) % arrSize;

            i++;
        }
    }

public:
    TablaHashCerrada_Agenda(int tamaniInicial)
    {
        this->tamanio = this->siguientePrimo(tamaniInicial);
        this->cantidadDeElementos = 0;
        array = new Asociacion *[this->tamanio]();
    }

    void insertar(string unaClave, int unValor)
    {
        this->insertar(this->array, this->tamanio, unaClave, unValor);

        if (this->factorDeCarga() > 0.7)
        {
            this->rehash();
        }
    }

    void imprimir()
    {
        cout << endl;
        for (int i = 0; i < this->tamanio; i++)
        {
            cout << "[ ";
            Asociacion *aux = array[i];
            if (aux != NULL)
            {
                cout << aux->clave << "/" << aux->valor << " ";
            }
            cout << "]" << endl;
        }
        cout << endl
             << "Factor de carga: " << this->factorDeCarga() << endl;
    }
};

int main()
{
    int opc = -1;
    int tamInit;
    cout << "Ingrese tam inicial de la tabla" << endl;
    cin >> tamInit;
    TablaHashCerrada_Agenda *tabla = new TablaHashCerrada_Agenda(tamInit);
    while (opc != 0)
    {
        cout << endl;
        cout << "Seleccione operacion:" << endl;
        cout << "0) Salir" << endl;
        cout << "1) Ingresar dato" << endl;
        cout << "2) Imprimir tabla" << endl;
        cout << "3) Generar datos de entrada" << endl;
        cout << endl;

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
                int cantidadDeLetras = (rand() % 10 + 1);
                for (int j = 0; j < cantidadDeLetras; j++)
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