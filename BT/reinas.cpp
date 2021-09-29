#include <string>
#include <iostream>
using namespace std;

bool esUnaCoordenadaValida(int c, int f, int N)
{
    return c < N && c >= 0 && f < N && f >= 0;
}

bool esSeguraDeColocar(int **tablero, int colActual, int fila, int N)
{

    for (int ci = colActual; ci >= 0; ci--)
    {
        if (tablero[fila][ci] == 1)
        {
            return false;
        }
    }
    for (int f = fila, c = colActual; esUnaCoordenadaValida(f, c, N); f--, c--)
    {
        if (tablero[f][c] == 1)
        {
            return false;
        }
    }
    for (int f = fila, c = colActual; esUnaCoordenadaValida(f, c, N); f++, c--)
    {
        if (tablero[f][c] == 1)
        {
            return false;
        }
    }
    return true;
}

void colocoLaReina(int **tablero, int col, int fila)
{
    tablero[fila][col] = 1;
}

void sacarLaReina(int **tablero, int col, int fila)
{
    tablero[fila][col] = 0;
}

bool esSolucion(int col, int N)
{
    // estoy en la ultima columna
    return col == N - 1;
}

void imprimir(int **tablero, int N)
{
    for (int fila = 0; fila < N; fila++)
    {
        for (int col = 0; col < N; col++)
        {
            cout << "[" << (tablero[fila][col] == 1 ? "*" : " ") << "] ";
        }
        cout << endl;
    }
}

void NReinas(int colActual, int N, int **tablero, bool &exito)
{
    if (!exito)
    {
        for (int fila = 0; fila < N; fila++)
        {
            if (!exito && esSeguraDeColocar(tablero, colActual, fila, N))
            {
                colocoLaReina(tablero, colActual, fila);

                if (esSolucion(colActual, N))
                {
                    imprimir(tablero, N);
                    exito = true;
                }
                else
                {
                    //  el paso siguiente
                    NReinas(colActual + 1, N, tablero, exito);
                }

                sacarLaReina(tablero, colActual, fila);
            }
        }
    }
}
void NReinasEnum(int colActual, int N, int **tablero, int &cantidadDeSoluciones)
{

    for (int fila = 0; fila < N; fila++)
    {
        if (esSeguraDeColocar(tablero, colActual, fila, N))
        {
            colocoLaReina(tablero, colActual, fila);

            if (esSolucion(colActual, N))
            {
                // imprimir(tablero, N);
                // cout << endl;
                cantidadDeSoluciones++;
            }
            else
            {
                //  el paso siguiente
                NReinasEnum(colActual + 1, N, tablero, cantidadDeSoluciones);
            }

            sacarLaReina(tablero, colActual, fila);
        }
    }
}

int main()
{
    int N;
    cin >> N;
    int **tablero = new int *[N];
    for (int i = 0; i < N; i++)
    {
        tablero[i] = new int[N]();
    }
    bool exito = false;
    // NReinas(0, N, tablero, exito);
    int cantidadDeSoluciones = 0;
    NReinasEnum(0, N, tablero, cantidadDeSoluciones);
    cout << "La cantidad de soluciones es " << cantidadDeSoluciones << endl;
    return 0;
}