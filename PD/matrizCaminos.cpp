#include <cassert>
#include <string>
#include <iostream>
using namespace std;

int matrizCaminos(int filas, int columnas)
{
    int **m = new int *[filas];
    for (int i = 0; i < filas; i++)
        m[i] = new int[columnas]();

    m[0][0] = 1;
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (i > 0 && j > 0)
            {
                m[i][j] = m[i - 1][j] + m[i][j - 1];
            }
            else if (j > 0)
            {
                m[i][j] = m[i][j - 1];
            }
            else if (i > 0)
            {
                m[i][j] = m[i - 1][j];
            }
        }
    }
    return m[filas - 1][columnas - 1];
}

int matrizCaminosObstaculos(int filas, int columnas, int obstaculos[3][5])
{
    int **m = new int *[filas];
    for (int i = 0; i < filas; i++)
        m[i] = new int[columnas]();

    m[0][0] = 1;
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (obstaculos[i][j] == 1)
            {
                m[i][j] = 0;
            }
            else if (i > 0 && j > 0)
            {
                m[i][j] = m[i - 1][j] + m[i][j - 1];
            }
            else if (j > 0)
            {
                m[i][j] = m[i][j - 1];
            }
            else if (i > 0)
            {
                m[i][j] = m[i - 1][j];
            }
        }
    }
    return m[filas - 1][columnas - 1];
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int matrizCaminosPesos(int filas, int columnas, int pesos[3][5])
{
    int **m = new int *[filas];
    for (int i = 0; i < filas; i++)
        m[i] = new int[columnas]();

    m[0][0] = pesos[0][0];
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            if (i > 0 && j > 0)
            {
                m[i][j] = pesos[i][j] + max(m[i - 1][j], m[i][j - 1]);
            }
            else if (j > 0)
            {
                m[i][j] = pesos[i][j] + m[i][j - 1];
            }
            else if (i > 0)
            {
                m[i][j] = pesos[i][j] + m[i - 1][j];
            }
        }
    }
    return m[filas - 1][columnas - 1];
}

int main()
{
    cout << matrizCaminos(3, 5) << endl;

    int obstaculos[3][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0},
    };
    cout << matrizCaminosObstaculos(3, 5, obstaculos) << endl;

    int pesos[3][5] = {
        {1, 3, 1, 1, 2},
        {2, 1, 1, 1, 1},
        {5, 4, 4, 2, 1},
    };
    cout << matrizCaminosPesos(3, 5, pesos) << endl;
    return 0;
}