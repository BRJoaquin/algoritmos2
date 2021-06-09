#include <cassert>
#include <string>
#include <iostream>
using namespace std;

int N = 8;

bool coordenadaValida(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < N; 
}

bool esSeguraDeColocar(int colCandidata, int filaCandidata, int **solucionCandidata)
{
    // reviso la horizonal
    for (int i = 0; i < N; i++)
    {
        if(solucionCandidata[filaCandidata][i] == 1) {
            return false;
        }
    }
    // ↘
    for (int fila = filaCandidata, columna = colCandidata; coordenadaValida(fila, columna) ; fila++,columna++)
    {
        if(solucionCandidata[fila][columna] == 1) {
            return false;
        }
    }
    // ↙
    for (int fila = filaCandidata, columna = colCandidata; coordenadaValida(fila, columna) ; fila++,columna--)
    {
        if(solucionCandidata[fila][columna] == 1) {
            return false;
        }
    }
    // ↗
    for (int fila = filaCandidata, columna = colCandidata; coordenadaValida(fila, columna) ; fila--,columna++)
    {
        if(solucionCandidata[fila][columna] == 1) {
            return false;
        }
    }
    // ↖
    for (int fila = filaCandidata, columna = colCandidata; coordenadaValida(fila, columna) ; fila--,columna--)
    {
        if(solucionCandidata[fila][columna] == 1) {
            return false;
        }
    }
    return true;
}
void colocarReina(int colActual, int filaCandidata, int **solucionCandidata)
{
    solucionCandidata[filaCandidata][colActual] = 1;
}
void retirarReina(int colActual, int filaCandidata, int **solucionCandidata)
{
    solucionCandidata[filaCandidata][colActual] = 0;
}
bool esUnaSolucion(int colActual)
{
    return colActual == N - 1;
}
void imprimirSolucion(int **solucionCandidata)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << "[" << (solucionCandidata[i][j] == 1 ? "*" : " ") << "] ";
        }
        cout << endl;
    }
    cout << endl;
}
void NReinas(int colActual, int **solucionCandidata, int &nroSoluciones)
{
    for (int filaCandidata = 0; filaCandidata < N; filaCandidata++)
    {
        // valido si puedo colocar la reina en dicha posicion
        if (esSeguraDeColocar(colActual, filaCandidata, solucionCandidata))
        {
            // realizo el paso
            colocarReina(colActual, filaCandidata, solucionCandidata); 
            // llegue a una solucion
            if (esUnaSolucion(colActual))
            {
                imprimirSolucion(solucionCandidata);
                nroSoluciones++;
            }
            else
            {
                // una vez colocada la reina y al ver que no llegue a una solucion voy por la siguiente columna
                NReinas(colActual + 1, solucionCandidata, nroSoluciones);
            }
            // lo retiro <- backtracking
            retirarReina(colActual, filaCandidata, solucionCandidata); 
        }
    }
}

int main()
{
    int **solucionCandidata = new int *[N];
    for (int i = 0; i < N; i++)
    {
        solucionCandidata[i] = new int[N]();
    }
    int nroSoluciones = 0;
    NReinas(0, solucionCandidata, nroSoluciones);
    cout << "Cantidad de soluciones: " << nroSoluciones << endl;
    return 0;
}