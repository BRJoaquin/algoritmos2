#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

int costos[7] = {0, 3, 1, 5, 8, 2, 1}; 


int escalerasPonderadas(int n) {
    int * costoMin = new int[n+1]();
    costoMin[0] = costos[0];
    costoMin[1] = costos[0] + costos[1];
    costoMin[2] = costos[0] + costos[2];

    for (int i = 3; i <= n; i++)
    {
        costoMin[i] = min(costoMin[i-1], costoMin[i-2]) + costos[i];
    }

    return costoMin[n];
}

int escalerasPonderadasCamino(int n) {
    int * costoMin = new int[n+1]();
    int * vengo = new int[n+1]();
    costoMin[0] = costos[0];
    vengo[0] = -1;
    costoMin[1] = costos[0] + costos[1];
    vengo[1] = 0;
    costoMin[2] = costos[0] + costos[2];
    vengo[2] = 0;


    for (int i = 3; i <= n; i++)
    {
        if(costoMin[i-1] < costoMin[i-2]) {
            costoMin[i] = costoMin[i-1] + costos[i];
            vengo[i] = i-1;
        } else{
            costoMin[i] = costoMin[i-2] + costos[i];
            vengo[i] = i-2;
        }
    }

    int actual = n;
    while(actual != 0) {
        cout << "vengo de " << actual << endl;
        actual = vengo[actual];
    } 

    return costoMin[n];
}

int escalerasPonderadasCaminov2(int n) {
    int * costoMin = new int[n+1]();
    costoMin[0] = costos[0];
    costoMin[1] = costos[0] + costos[1];
    costoMin[2] = costos[0] + costos[2];

    for (int i = 3; i <= n; i++)
    {
        costoMin[i] = min(costoMin[i-1], costoMin[i-2]) + costos[i];
    }

    int actual = n;
    while(actual != 0) {
        cout << "vengo de " << actual << endl;
        actual -= costoMin[actual-1] < costoMin[actual-2] ? 1 : 2;
    }

    return costoMin[n];
}


int main()
{
    cout << escalerasPonderadasCaminov2(6) << endl;
}