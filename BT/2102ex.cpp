#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;
struct Reunion {
    int horaInicio;
    int horaFin;
    int grupo;
};

bool todosTrue(bool *arr, int largo) {
    for (int i = 0; i < largo; i++)
    {
        if(!arr[i]) {
            return false;
        }
    }
    return true;
}

bool esSolucion(List<Reunion> * agendaCandidata, int cantGrupos) {
    bool *estaEnLaReunion = new bool[cantGrupos];
    Iterador<Reunion> it = agendaCandidata->getIterador();
    while(!it->termino()) {
        Reunion r = it->siguiente();
        estaEnLaReunion[r.grupo] = true;
    }
    return todosTrue(estaEnLaReunion, cantGrupos);
}

bool esMejorSolucion(List<Reunion> * agendaCandidata, List<Reunion>*mejorAgenda) {
    return agendaCanidata->length() > mejorAgenda->length();
}

void clonarSolucion(List<Reunion> * origen, List<Reunion>* &destino) {
    // idealmente liberar la memoria de mejorAgenda
    destino = new Lista<Reunion>();
    Iterador<Reunion> it = origen->getIterador();
    while(!it->termino()) {
        Reunion r = it->siguiente();
        destino->add(r);
    }
}

bool estaAgendada(List<Reunion> * agendaCandidata, Reunion r) {
    return agendaCandidata->exists(r);
}

bool puedoIrALaReunion(List<Reunion> * agendaCandidata, Reunion reunionCandidata) {
    Iterador<Reunion> it = origen->getIterador();
    while(!it->termino()) {
        Reunion r = it->siguiente();
        if(!(reunionCandidata.fin <= r.inicio || reunionCandidata.inicio >= r.fin)) {
            return false;
        }
    }
    return true;
}

void agendarReunion(List<Reunion> * agendaCandidata, Reunion reunion) {
    agendaCandidata->add(reunion);
}
void desagendarReunion(List<Reunion> * agendaCandidata, Reunion reunion) {
    agendaCandidata->remove(reunion);
}

void reunionesBT(Reunion* reuniones, int cantReuniones,  int
        cantGrupos, List<Reunion> * agendaCandidata, List<Reunion>* &mejorAgenda)
{
    if (esSolucion(agendaCandidata, cantGrupos) && esMejorSolucion(agendaCandidata, mejorAgenda))
    {
        clonarSolucion(agendaCandidata, mejorAgenda);
    }
    else
    {
        for (int i = 0; i < cantReuniones; i++)
        {
            Reunion reunion = reuniones[i];
            if (!estaAgendada(agendaCandidata, reunion) && puedoIrALaReunion(agendaCandidata, reunion))
            {
                agendarReunion(agendaCandidata, reunion);
                reunionesBT(reuniones, cantReuniones, cantGrupos, agendaCandidata, mejorAgenda);
                desagendarReunion(agendaCandidata, reunion);
            }
        }
    }
}

Lista<Reunion>* horario(Reunion* reuniones, int cantReuniones, int cantGrupos) {
    Lista<Reunion> * sandbox = new Lista<Reunion>();
    Lista<Reunion> * solucion = new Lista<Reunion>();
    reunionesBT(reuniones,cantReuniones, cantGrupos, sandbox, solucion);
    return solucion;
}