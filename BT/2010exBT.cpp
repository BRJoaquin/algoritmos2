#include <cassert>
#include <string>
#include <iostream>
#include <climits>
using namespace std;
#define N 4
#define costoTierra 10
#define costoMetal 5
#define costoCompuerta 30
#define costoPared 18910

struct Coordenada {
    int x;
    int y;
    Coordenada(int x, int y) : x(x), y(y) {}
};

bool puedoPodar(int costoActual, int mejorCosto) {
    return costoActual > mejorCosto;
}

bool coordeanadaValida(Coordenada origen) {
    return origen.x >= 0 && origen.x < N && origen.y >= 0 && origen.y < N;
}

bool noCompaMuerto(Coordenada origen, char tablero[N][N]) {
    return tablero[origen.x][origen.y] != 'F';
}

bool movimientoPosible(Coordenada origen, char tablero[N][N],bool pase[N][N]) {
    return coordeanadaValida(origen) && !pase[origen.x][origen.y] && noCompaMuerto(origen, tablero);
}

int costoDePasar(Coordenada origen, char tablero[N][N]) {
    if (tablero[origen.x][origen.y] == 'T') {
        return costoTierra;
    } else if (tablero[origen.x][origen.y] == 'M') {
        return costoMetal;
    } else if (tablero[origen.x][origen.y] == 'P') {
        return costoPared;
    } else {
        return costoCompuerta;
    }
}

void realizarMovimiento(Coordenada origen, char tablero[N][N], bool pase[N][N], List<Coordenada> *camino, int &costoCamino) {
    pase[origen.x][origen.y] = true;
    // aniadimos al final de la lista
    camino->add(origen);
    costoCamino += costoDePasar(origen, tablero);
}
void quitarMovimiento(Coordenada origen, char tablero[N][N], bool pase[N][N], List<Coordenada> *camino, int &costoCamino) {
    pase[origen.x][origen.y] = false;
    // remover el final de la lista
    camino->remove(origen);
    costoCamino -= costoDePasar(origen, tablero);
}

bool esSolucion(Coordenada origen, Coordenada destino) {
    return origen.x == destino.x && origen.y == destino.y;
}

bool esMejorSolucion(int costoCamino, int mejorCostoCamino) {
    return costoCamino < mejorCostoCamino;
}

void actualizarMejorSolucion(List<Coordenada> *camino, int costoCamino, List<Coordenada> *mejorCamino, int &mejorCostoCamino) {
    mejorCamino = camino->clone();
    mejorCostoCamino = costoCamino;
}

void oMeApuroOMeOperanBT(Coordenada origen, Coordenada destino, char tablero[N][N],bool pase[N][N], List<Coordenada> *camino, int costoCamino, List<Coordenada> *mejorCamino, int &mejorCostoCamino) {
    if(!puedoPodar(costoCamino, mejorCostoCamino)) {
        if(movimientoPosible(origen, tablero, pase)) {
            realizarMovimiento(origen, tablero, pase, camino, costoCamino);
            if(esSolucion(origen, destino) && esMejorSolucion(costoCamino, mejorCostoCamino)) {
                actualizarMejorSolucion(camino, costoCamino, mejorCamino, mejorCostoCamino);
            }else{
                // movimientos posibles
                int dX[4] = {1, 0, -1, 0};
                int dY[4] = {0, 1, 0, -1};
                for (int i = 0; i < 4; i++)
                {
                    Coordenada nuevaPosicion = Coordenada(origen.x + dX[i], origen.y + dY[i]);
                    oMeApuroOMeOperanBT(nuevaPosicion, destino, tablero, pase, camino, costoCamino, mejorCamino, mejorCostoCamino);
                }
            }
            quitarMovimiento(pase, camino, costoCamino);
        }
    }
}


List<Coordenada>* oMeApuroOMeOperan(Coordenada origen, Coordenada destino, char tablero[N][N]) {
    List<Coordenada>* camino = new List<Coordenada>();
    List<Coordenada>* solucion = new List<Coordenada>();
    int mejorCosto = INT_MAX;
    bool pase[N][N] = {
                            {false, false, false, false},
                            {false, false, false, false},
                            {false, false, false, false},
                            {false, false, false, false}
                        };
    oMeApuroOMeOperanBT(origen, destino, tablero, pase, camino, 0, solucion, mejorCosto);
    return solucion;
}

int main()
{
    Coordenada origen(0, 0);
    Coordenada destino(3, 3);
    char tablero[N][N] = {
                            {'T', 'T', 'F', 'F'},
                            {'F', 'T', 'C', 'T'},
                            {'T', 'T', 'C', 'P'},
                            {'T', 'F', 'T', 'T'}
                        };
    return 0;
}