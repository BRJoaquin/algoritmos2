#include <string>
#include <iostream>
using namespace std;

#define N 7

bool hayQuePodar(int cantMov, int sushiRestante, int mejorSolucion)
{
    // si llevo X movimiento y necesito me restan Y sushies no pueden superar mi mejor solucion (es imposible enctrar desde ahi una mejor solucion)
    return cantMov + sushiRestante > mejorSolucion;
}
bool coordenadaValida(int f, int c)
{
    return f >= 0 && f < N && c >= 0 && c < N;
}
bool paseTresVeces(int filaC, int colC, int **pase)
{
    return pase[filaC][colC] >= 3;
}
bool esPared(int filaC, int colC, char matriz[N][N])
{
    return matriz[filaC][colC] == 'P';
}

bool esMovimientoValido(int filaC, int colC, int **pase, char matriz[N][N])
{
    return coordenadaValida(filaC, colC) && !paseTresVeces(filaC, colC, pase) && !esPared(filaC, colC, matriz);
}
void aplicoMovimiento(int filaC, int colC, int **pase, char matriz[N][N], int &sushiRestante, int &salsaPos, int cantMov)
{
    if(pase[filaC][colC] == 0) {
        if (matriz[filaC][colC] == 'S')
        {
            // marcos cuando comi la salsa
            salsaPos = cantMov;
        }
        else
        {
            // si habia un sushi, le resto a los que me quedan
            sushiRestante--;
        }
    }
    // marco que pase una vez mas por ahi
    pase[filaC][colC]++;
}
void quitoMovimiento(int filaC, int colC, int **pase, char matriz[N][N], int &sushiRestante, int &salsaPos, int cantMov)
{
    if(pase[filaC][colC] == 1) {
        if (matriz[filaC][colC] == 'S')
        {
            salsaPos = -1;
        }
        else
        {
            sushiRestante++;
        }
    }
    pase[filaC][colC]--;
}
bool esSolucion(int sushiRestante, int salsaPos)
{
    // no me quedan sushi para comer y me comi la salsa
    return sushiRestante == 0 && salsaPos != -1;
}
bool esMejorSolucion(int cantMov, int mejorCantMov, int salsaPos, int mejorSalsaPos)
{
    // si lo hice en menos pasos o lo hice en iguales pasos pero comi la salsa antes
    return (cantMov < mejorCantMov) || (cantMov == mejorCantMov && salsaPos < mejorSalsaPos);
}
void intercambiar(int i,int r, int arr[4]) {
    int aux = arr[r];
    arr[r] = arr[i];
    arr[i] = aux;
}
void pacmanBT(int filaC, int colC, int sushiRestante, int **pase, char matriz[N][N],
              int cantMov, int salsaPos, int &mejorCantMov, int &mejorSalsaPos)
{
    if (!hayQuePodar(cantMov, sushiRestante, mejorCantMov))
    {
        if (esMovimientoValido(filaC, colC, pase, matriz))
        {
            aplicoMovimiento(filaC, colC, pase, matriz, sushiRestante, salsaPos, cantMov);
            if (esSolucion(sushiRestante, salsaPos) && esMejorSolucion(cantMov, mejorCantMov, salsaPos, mejorSalsaPos))
            {
                // cout << "encontre una solucion " <<  cantMov << " " << salsaPos <<endl;
                mejorCantMov = cantMov;
                mejorSalsaPos = salsaPos;
            }
            else
            {
                // veo alternativas
                int dx[4] = {-1, 0, 0, 1};
                int dy[4] = {0, 1, -1, 0};
                
                for (int i = 0; i < 4; i++)
                {
                    pacmanBT(filaC + dx[i], colC + dy[i], sushiRestante, pase, matriz, cantMov + 1, salsaPos, mejorCantMov, mejorSalsaPos);
                }
            }
            quitoMovimiento(filaC, colC, pase, matriz, sushiRestante, salsaPos, cantMov);
        }
    }
}

int pacman(char matriz[N][N])
{
    int cantSushiOriginal = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (matriz[i][j] == 'N')
            {
                cantSushiOriginal++;
            }
        }
    }
    int **pase = new int *[N];
    for (int i = 0; i < N; i++)
    {
        pase[i] = new int[N]();
    }

    int longMasCorta = 100;
    int mejorPosSalsa = -1;
    pacmanBT(0, 0, cantSushiOriginal, pase, matriz, 1, -1, longMasCorta, mejorPosSalsa);
    cout << longMasCorta << endl;
    cout << mejorPosSalsa << endl;

    return longMasCorta;
}

int main()
{
    char tablero[N][N] = {
        {'N', 'N', 'N', 'N', 'N', 'N', 'P'},
        {'P', 'P', 'P', 'P', 'N', 'P', 'P'},
        {'P', 'N', 'N', 'N', 'N', 'N', 'N'},
        {'N', 'N', 'P', 'S', 'P', 'P', 'N'},
        {'N', 'P', 'P', 'N', 'P', 'N', 'N'},
        {'N', 'N', 'P', 'N', 'N', 'N', 'P'},
        {'P', 'N', 'N', 'N', 'P', 'N', 'N'}};
    pacman(tablero);
    return 0;
}