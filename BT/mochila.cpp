#include <cassert>
#include <string>
#include <iostream>
using namespace std;

int const N = 4;
int pesos[N] = {5, 3, 8, 4};
int valores[N] = {10, 20, 25, 8};
int capacidadMochila = 12;

bool esUnObjetoValido(int objeto)
{
    return objeto < N;
}
bool puedoPonerElObjeto(int objeto, int capacidadActual)
{
    return capacidadActual >= pesos[objeto];
}
void colocarTentativamenteElObjeto(int objeto, int &capacidadActual, int &valorCandidato)
{
    capacidadActual -= pesos[objeto];
    valorCandidato += valores[objeto];
}
void retirarElObjeto(int objeto, int &capacidadActual, int &valorCandidato)
{
    capacidadActual += pesos[objeto];
    valorCandidato -= valores[objeto];
}
bool esSolucion()
{
    return true; // todas son soluciones
}
bool esMejorSolucion(int valorCandidato, int mejorValor)
{
    return valorCandidato > mejorValor;
}

void mochila01(int objeto, int capacidadActual, int valorCandidato, int &mejorValor)
{
    if (esUnObjetoValido(objeto))
    {
        for (int alternativa = 0; alternativa <= 1; alternativa++)
        {
            bool pongoElObjeto = alternativa == 0;
            // seria un movimiento valido para realizar
            if (pongoElObjeto)
            {
                if (puedoPonerElObjeto(objeto, capacidadActual))
                {
                    // aplicamos el movimiento
                    colocarTentativamenteElObjeto(objeto, capacidadActual, valorCandidato);

                    // si llegamos al destino, entontramos una solucion
                    if (esSolucion() && esMejorSolucion(valorCandidato, mejorValor))
                    {
                        mejorValor = valorCandidato;
                    }
                    // exploro el siguiente objeto
                    mochila01(objeto + 1, capacidadActual, valorCandidato, mejorValor);

                    // deshacemos el movimiento
                    retirarElObjeto(objeto, capacidadActual, valorCandidato);
                }
            }
            else
            {
                mochila01(objeto + 1, capacidadActual, valorCandidato, mejorValor);
            }
        }
    }
}

void mochilaINF(int objeto, int capacidadActual, int valorCandidato, int &mejorValor)
{
    if (esUnObjetoValido(objeto))
    {
        for (int alternativa = 0; alternativa <= 1; alternativa++)
        {
            bool pongoElObjeto = alternativa == 0;
            // seria un movimiento valido para realizar
            if (pongoElObjeto)
            {
                if (puedoPonerElObjeto(objeto, capacidadActual))
                {
                    // aplicamos el movimiento
                    colocarTentativamenteElObjeto(objeto, capacidadActual, valorCandidato);

                    // si llegamos al destino, entontramos una solucion
                    if (esSolucion() && esMejorSolucion(valorCandidato, mejorValor))
                    {
                        mejorValor = valorCandidato;
                    }
                    // exploro el siguiente objeto
                    mochilaINF(objeto + 1, capacidadActual, valorCandidato, mejorValor);
                    // trato de volver a ponerlo
                    mochilaINF(objeto, capacidadActual, valorCandidato, mejorValor);

                    // deshacemos el movimiento
                    retirarElObjeto(objeto, capacidadActual, valorCandidato);
                }
            }
            else
            {
                mochilaINF(objeto + 1, capacidadActual, valorCandidato, mejorValor);
            }
        }
    }
}

void colocarTentativamenteElObjetoRec(int objeto, int &capacidadActual, int &valorCandidato, int objetosUsados[N])
{
    capacidadActual -= pesos[objeto];
    valorCandidato += valores[objeto];
    objetosUsados[objeto] = 1;
}
void retirarElObjetoRec(int objeto, int &capacidadActual, int &valorCandidato, int objetosUsados[N])
{
    capacidadActual += pesos[objeto];
    valorCandidato -= valores[objeto];
    objetosUsados[objeto] = 0;
}
void clonarSolucion(int origen[N], int destino[N])
{
    for (int i = 0; i < N; i++)
    {
        destino[i] = origen[i];
    }
}

void mochila01Rec(int objeto, int capacidadActual, int valorCandidato, int objetosUsados[N], int &mejorValor, int mejorObjetosUsados[N])
{
    if (esUnObjetoValido(objeto))
    {
        for (int alternativa = 0; alternativa <= 1; alternativa++)
        {
            bool pongoElObjeto = alternativa == 0;
            // seria un movimiento valido para realizar
            if (pongoElObjeto)
            {
                if (puedoPonerElObjeto(objeto, capacidadActual))
                {
                    // aplicamos el movimiento
                    colocarTentativamenteElObjetoRec(objeto, capacidadActual, valorCandidato, objetosUsados);

                    // si llegamos al destino, entontramos una solucion
                    if (esSolucion() && esMejorSolucion(valorCandidato, mejorValor))
                    {
                        clonarSolucion(objetosUsados, mejorObjetosUsados);
                        mejorValor = valorCandidato;
                    }
                    // exploro el siguiente objeto
                    mochila01Rec(objeto + 1, capacidadActual, valorCandidato, objetosUsados, mejorValor, mejorObjetosUsados);

                    // deshacemos el movimiento
                    retirarElObjetoRec(objeto, capacidadActual, valorCandidato, objetosUsados);
                }
            }
            else
            {
                mochila01Rec(objeto + 1, capacidadActual, valorCandidato, objetosUsados, mejorValor, mejorObjetosUsados);
            }
        }
    }
}

int main()
{
    // CASO 1: mochila 0 1
    // int valorMochila = 0;
    // mochila01(0, capacidadMochila, 0, valorMochila);
    // cout << "El valor de la mochila es " << valorMochila << endl;

    // CASO 2: mochila INF
    // int valorMochila = 0;
    // mochila01(0, capacidadMochila, 0, valorMochila);
    // cout << "El valor de la mochila es " << valorMochila << endl;

    // CASO 3: mochila 0 1 recorrido
    int valorMochila = 0;
    int playground[N] = {0, 0, 0, 0};
    int solucion[N] = {0, 0, 0, 0};
    mochila01Rec(0, capacidadMochila, 0, playground, valorMochila, solucion);
    cout << "El valor de la mochila es " << valorMochila << endl;
    for (int i = 0; i < N; i++)
    {
        if (solucion[i] == 1)
        {
            cout << "Use el objeto " << (i + 1) << " peso:" << pesos[i] << " valor:" << valores[i] << endl;
        }
    }

    return 0;
}