#include <cassert>
#include <string>
#include <iostream>
#include <climits>
using namespace std;

bool perteneceAlTablero(int filaOri, int colOri)
{
    return filaOri >= 0 && filaOri < 8 && colOri >= 0 && colOri < 8;
}
bool pase(int filaOri, int colOri, int tablero[8][8])
{
    return tablero[filaOri][colOri] != 0;
}
void colocarTentativamenteElCaballo(int filaOri, int colOri, int nroMov, int tablero[8][8])
{
    tablero[filaOri][colOri] = nroMov;
}
void retirarElCaballo(int filaOri, int colOri, int tablero[8][8])
{
    tablero[filaOri][colOri] = 0;
}
bool llegueAlDestino(int filaOri, int colOri, int filaDes, int colDes)
{
    return filaOri == filaDes && colOri == colDes;
}
void mostrarTablero(int tablero[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << "[";
            if (tablero[i][j] != 0)
            {
                if (tablero[i][j] < 10)
                {
                    cout << " ";
                }
                cout << tablero[i][j];
            }
            else
            {
                cout << "  ";
            }
            cout << "] ";
        }
        cout << endl;
    }
    cout << endl;
}

void caminoCaballo(int filaOri, int colOri, int filaDes, int colDes, int nroMov, int tablero[8][8], bool &exito)
{
    // seria un movimiento valido para realizar
    if (!exito && perteneceAlTablero(filaOri, colOri) && !pase(filaOri, colOri, tablero))
    {
        // aplicamos el movimiento
        colocarTentativamenteElCaballo(filaOri, colOri, nroMov, tablero);
        // si llegamos al destino, entontramos una solucion
        if (llegueAlDestino(filaOri, colOri, filaDes, colDes))
        {
            mostrarTablero(tablero);
            exito = true;
        }
        else
        {
            int dFilas[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
            int dColumnas[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

            for (int alternativa = 0; alternativa < 8; alternativa++)
            {
                caminoCaballo(filaOri + dFilas[alternativa], colOri + dColumnas[alternativa], filaDes, colDes, nroMov + 1, tablero, exito);
            }
        }
        // deshacemos el movimiento
        retirarElCaballo(filaOri, colOri, tablero);
    }
}

void caminoCaballoV2(int filaOri, int colOri, int filaDes, int colDes, int nroMov, int tablero[8][8], bool &exito)
{
    // si aun no logre llegar
    if (!exito)
    {
        int dFilas[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
        int dColumnas[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

        for (int alternativa = 0; alternativa < 8; alternativa++)
        {
            int filaTent = filaOri + dFilas[alternativa];
            int colTent = colOri + dColumnas[alternativa];
            // seria un movimiento valido para realizar
            if (perteneceAlTablero(filaTent, colTent) && !pase(filaTent, colTent, tablero))
            {
                // aplicamos el movimiento
                colocarTentativamenteElCaballo(filaTent, colTent, nroMov, tablero);
                // si llegamos al destino, entontramos una solucion
                if (llegueAlDestino(filaTent, colTent, filaDes, colDes))
                {
                    mostrarTablero(tablero);
                    exito = true;
                }
                else
                {
                    caminoCaballoV2(filaTent, colTent, filaDes, colDes, nroMov + 1, tablero, exito);
                }
                // deshacemos el movimiento
                retirarElCaballo(filaOri, colOri, tablero);
            }
        }
    }
}

void clonarTablero(int origen[8][8], int destino[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            destino[i][j] = origen[i][j];
        }
    }
}

void mejorCaminoCaballo(int filaOri, int colOri, int filaDes, int colDes, int nroMov, int tablero[8][8], int mejorTablero[8][8], int &mejorNroMov)
{
    // seria un movimiento valido para realizar
    if (perteneceAlTablero(filaOri, colOri) && !pase(filaOri, colOri, tablero))
    {
        // aplicamos el movimiento
        colocarTentativamenteElCaballo(filaOri, colOri, nroMov, tablero);
        // si llegamos al destino, entontramos una solucion
        if (llegueAlDestino(filaOri, colOri, filaDes, colDes) && nroMov < mejorNroMov)
        {
            clonarTablero(tablero, mejorTablero);
            mejorNroMov = nroMov;
        }
        else
        {
            int dFilas[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
            int dColumnas[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

            for (int alternativa = 0; alternativa < 8; alternativa++)
            {
                mejorCaminoCaballo(filaOri + dFilas[alternativa], colOri + dColumnas[alternativa], filaDes, colDes, nroMov + 1, tablero, mejorTablero, mejorNroMov);
            }
        }
        // deshacemos el movimiento
        retirarElCaballo(filaOri, colOri, tablero);
    }
}

bool hayQuePodar(int nroMov, int mejorNroMov)
{
    return nroMov >= mejorNroMov;
}

void mejorCaminoCaballoV2(int filaOri, int colOri, int filaDes, int colDes, int nroMov, int tablero[8][8], int mejorTablero[8][8], int &mejorNroMov)
{
    // poda: si en el la solucion candidata actual ya llevamos mas que la (por ahora) mejor solucion, entonces lo descartamos
    if (!hayQuePodar(nroMov, mejorNroMov))
    {
        // seria un movimiento valido para realizar
        if (perteneceAlTablero(filaOri, colOri) && !pase(filaOri, colOri, tablero))
        {
            // aplicamos el movimiento
            colocarTentativamenteElCaballo(filaOri, colOri, nroMov, tablero);
            // si llegamos al destino, entontramos una solucion
            if (llegueAlDestino(filaOri, colOri, filaDes, colDes) && nroMov < mejorNroMov)
            {
                clonarTablero(tablero, mejorTablero);
                mejorNroMov = nroMov;
            }
            else
            {
                int dFilas[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
                int dColumnas[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

                for (int alternativa = 0; alternativa < 8; alternativa++)
                {
                    mejorCaminoCaballoV2(filaOri + dFilas[alternativa], colOri + dColumnas[alternativa], filaDes, colDes, nroMov + 1, tablero, mejorTablero, mejorNroMov);
                }
            }
            // deshacemos el movimiento
            retirarElCaballo(filaOri, colOri, tablero);
        }
    }
}

bool noProhibido(int filaOri, int colOri, int prohibidos[8][8])
{
    return prohibidos[filaOri][colOri] == 0;
}

void mejorCaminoCaballoRestricciones(int filaOri, int colOri, int filaDes, int colDes, int nroMov, int tablero[8][8], int mejorTablero[8][8], int &mejorNroMov, int prohibidos[8][8])
{
    // poda: si en el la solucion candidata actual ya llevamos mas que la (por ahora) mejor solucion, entonces lo descartamos
    if (!hayQuePodar(nroMov, mejorNroMov))
    {
        // seria un movimiento valido para realizar
        if (perteneceAlTablero(filaOri, colOri) && !pase(filaOri, colOri, tablero) && noProhibido(filaOri, colOri, prohibidos))
        {
            // aplicamos el movimiento
            colocarTentativamenteElCaballo(filaOri, colOri, nroMov, tablero);
            // si llegamos al destino, entontramos una solucion
            if (llegueAlDestino(filaOri, colOri, filaDes, colDes) && nroMov < mejorNroMov)
            {
                clonarTablero(tablero, mejorTablero);
                mejorNroMov = nroMov;
            }
            else
            {
                int dFilas[8] = {-2, -2, -1, 1, 2, 2, 1, -1};
                int dColumnas[8] = {-1, 1, 2, 2, 1, -1, -2, -2};

                for (int alternativa = 0; alternativa < 8; alternativa++)
                {
                    mejorCaminoCaballoRestricciones(filaOri + dFilas[alternativa], colOri + dColumnas[alternativa], filaDes, colDes, nroMov + 1, tablero, mejorTablero, mejorNroMov, prohibidos);
                }
            }
            // deshacemos el movimiento
            retirarElCaballo(filaOri, colOri, tablero);
        }
    }
}

void mostrarTableroProhibidos(int tablero[8][8], int prohibidos[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << "[";
            if (tablero[i][j] != 0)
            {
                if (tablero[i][j] < 10)
                {
                    cout << " ";
                }
                cout << tablero[i][j];
            }
            else if (prohibidos[i][j] == 1)
            {
                cout << "**";
            }
            else
            {
                cout << "  ";
            }
            cout << "] ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    // CASO 1: una solucion cualquiera
    // int tablero[8][8] = {
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0}};
    // bool exito = false;
    // caminoCaballo(0, 0, 7, 7, 1, tablero, exito);

    // int tablero2[8][8] = {
    //     {1, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0}};
    // bool exito2 = false;
    // caminoCaballoV2(0, 0, 7, 7, 2, tablero2, exito2);

    // CASO 2: la mejor solucion (camino mas corto)
    // int tableroPlayground[8][8] = {
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0}};
    // int mejorSolucion[8][8] = {
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0}};
    // int mejorNroMov = INT_MAX;
    // // no va a terminar, son muchas posibilidades
    // // mejorCaminoCaballo(0, 0, 7, 7, 1, tableroPlayground, mejorSolucion, mejorNroMov);
    // // con poda
    // mejorCaminoCaballoV2(0, 0, 7, 7, 1, tableroPlayground, mejorSolucion, mejorNroMov);
    // mostrarTablero(mejorSolucion);

    // CASO 3: la mejor solucion (camino mas corto) + restricciones
    int tableroPlayground[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    int mejorSolucion[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    int prohibidos[8][8] = {
        {0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 1, 1, 1, 0, 0, 1},
        {0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    int mejorNroMov = INT_MAX;
    mejorCaminoCaballoRestricciones(0, 0, 7, 7, 1, tableroPlayground, mejorSolucion, mejorNroMov, prohibidos);
    mostrarTableroProhibidos(mejorSolucion, prohibidos);

    return 0;
}