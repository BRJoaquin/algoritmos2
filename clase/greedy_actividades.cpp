#include <string>
#include <iostream>
#include <climits>
#include <cassert>
#include <algorithm>

using namespace std;

struct Actividad {
    string banda;
    int inicio;
    int fin;
};

bool comparadorFin(Actividad a1, Actividad a2) {
    return a1.fin < a2.fin;
}


void seleccionaActividades(Actividad actividades[], int n) {
    sort(actividades, actividades + n, comparadorFin);

    cout << actividades[0].banda <<  " " << actividades[0].inicio << "-" << actividades[0].fin << endl;
    int estoyOcupadoHasta = actividades[0].fin;

    for (int i = 1; i < n; i++)
    {
        if(actividades[i].inicio >= estoyOcupadoHasta) {
            cout << actividades[i].banda <<  " " << actividades[i].inicio << "-" << actividades[i].fin << endl;
            estoyOcupadoHasta = actividades[i].fin;
        }
    }
}


int main()
{
    Actividad actividades[] = {
        {"Tony Velour", 1200, 1230},
        {"Redveil", 1230, 1315},
        {"Niko Rubio", 1250, 1330},
        {"Last Dinosaurs", 1315, 1400},
        {"Mills", 1300, 1340},
        {"Midwxst", 1350, 1430},
        {"Sam Fender", 1400, 1500},
        {"Petey", 1450, 1530},
        {"Willie Jones", 1410, 1450},
        {"Inhaler", 1500, 1600},
        {"Role Model", 1600, 1700},
        {"Zach Bryan", 1600, 1645},
        {"Giovannie and the Hired Guns", 1630, 1710},
        {"Tove Lo", 1700, 1800},
        {"100 Gecs", 1800, 1900},
        {"Remi Wolf", 1830, 1915},
        {"Maxo Kream", 1945, 2030},
        {"Lil Baby", 2045, 2200},
        {"Caroline Polachek", 2100, 2200},
        {"Jubilee", 1300, 1345},
        {"Bijou", 1400, 1500},
        {"Tsha", 1515, 1615},
        {"Chris Lorenzo", 1630, 1730},
        {"MK", 1745, 1845},
        {"Black Coffee", 1900, 2000},
        {"Zhu", 2030, 2145},
        {"Emmy Meli", 1200, 1245},
        {"Underscores", 1245, 1330},
        {"Sampa the Great", 1330, 1415},
        {"Maude Latour", 1415, 1515},
        {"Still Woozy", 1615, 1715},
        {"Manchester Orchestra", 1715, 1815},
        {"Billy Strings", 1815, 1915},
        {"Ashnikko", 1915, 2015},
        {"Metallica", 2015, 2230}
    };
    int n = sizeof(actividades) / sizeof(actividades[0]);

    seleccionaActividades(actividades, n);
}