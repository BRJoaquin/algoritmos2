#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;


MinHeap * cargarAristas(Grafo *g) {
    int V = g->getV();
    // como maximo el heap puede tener V*V arsistas
    MinHeap * heap = new MinHeap(V*V);
    for(int v= 1; v <= V; v++) {
        Iterador<Arista> arista = g->adyacentesA(v);
        while(!arista->termino()) {
            Arista arista = arista->siguiente();
            heap->insertar(arista);
        }
    }
    return heap;
}

// la idea es basicamente usar Kruskal
// aquellas aristas aceptadas seran las que se hace mantenimiento
// aquellas arsitas no aceptadas iran a cobre.
void mantenimiento(Grafo *g) {
    int totalMantenimiento = 0;
    int totalACobre = 0;
    // cargo todas las aristas en un heap para poder ir sacando de forma ordenada
    MinHeap * aristas = cargarAristas(g);
    // se utiliza un mfset como estructura auxiliar para saber si dos vertices
    // no estan conectados previamente
    MFSet sets(V + 1);
    while(!arsitas->vacio()) {
        Arsita arista = arsitas->getMin();
        arsitas->eliminarMin();
        int origen = arista.origen;
        int destino = arista.destino;
        if(sets.find(origen) != sets.find(destino)) {
            totalMantenimiento+=arsita.peso;
            sets.merge(origen, destino);
        }else{
            totalACobre+=arsita.peso;
        }
    }
    // imprimo resultados
    cout << totalMantenimiento << endl;
    cout << totalACobre << endl;
}
