#include <iostream>
#include <limits.h>
#include <cassert>
#include <string.h>
using namespace std;

void rompeMuros(int laberinto[5][10], int origenX, int destinoX)
{
    int origenY = 0;
    int destinoY = 9;
    int murosRotos = 0;

    string camino[5][10] = {
        {"*", "*", "*", "*", "*", "*", "*", "*", "*", "*"},
        {"*", "*", "*", "*", "*", "*", "*", "*", "*", "*"},
        {"*", "*", "*", "*", "*", "*", "*", "*", "*", "*"},
        {"*", "*", "*", "*", "*", "*", "*", "*", "*", "*"},
        {"*", "*", "*", "*", "*", "*", "*", "*", "*", "*"}};

    camino[origenX][origenY] = "O";
    camino[destinoX][destinoY] = "D";

    while (origenX != destinoX && origenY != destinoY)
    {

        int diffY = destinoY - origenY;
        // diffX > 0 tengo que ir hacia "abajo"
        // diffX < 0 tengo que ir hacia "arriba"
        // diffX == 0 estoy en la misma linea horizontal
        int diffX = destinoX - origenX;
        int sumX = diffX > 0 ? 1 : -1;
        // en el caso de que me tenga avanzar para ambos lados
        if (diffY != 0 && diffX != 0)
        {
            // en el caso de que pueda ir vertical y horizontalmente hacia el destino sin rompero un muro
            if (laberinto[origenX][origenY + 1] == 0 && laberinto[origenX + sumX][origenY] == 0)
            {
                // si estoy mas lejos horizontalmente que verticalmente prefiero moverme horizontalmente
                if (diffY > abs(diffX))
                {
                    origenY++;
                }
                // en otro caso me muevo verticalmente
                else
                {
                    origenX += sumX;
                }
            }
            // en el caso de que tengo una pared horizontalmente pero no verticalmente
            else if (laberinto[origenX][origenY + 1] == 1 && laberinto[origenX + sumX][origenY] == 0)
            {
                // me muevo verticalmente
                origenX += sumX;
            }
            // en el caso de que tengo una pared verticalmente pero no horizontalmente
            else if (laberinto[origenX][origenY + 1] == 0 && laberinto[origenX + sumX][origenY] == 1)
            {
                // me muevo horizontalmente (hacia la derecha)
                origenY++;
            }
            // en el caso de que tenga paredes hacia ambas direcciones
            else
            {
                // si estoy mas lejos horizontalmente que verticalmente prefiero moverme horizontalmente
                if (diffY > abs(diffX))
                {
                    origenY++;
                }
                // en otro caso me muevo verticalmente
                else
                {
                    origenX += sumX;
                }
                murosRotos++;
            }
        }
        // ya estoy en la misma linea horizontal, avanzo hacia la derecha
        else if (diffX == 0)
        {
            if (laberinto[origenX][origenY + 1] == 1)
            {
                murosRotos++;
            }
            origenY++;
        }
        // ya estoy en la misma linea vertical, avanzo arriba/abajo
        else
        {
            if (laberinto[origenX + sumX][origenY] == 1)
            {
                murosRotos++;
            }
            origenX += sumX;
        }

        camino[origenX][origenY] = laberinto[origenX][origenY] == 1 ? "X" : "-";
    }

    cout << "Muros Rotos " << murosRotos << endl;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << camino[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{

    int labertinto[5][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 1, 0, 1, 0, 0, 1},
        {0, 0, 0, 1, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0}};
    rompeMuros(labertinto, 2, 4);
    return 0;
}