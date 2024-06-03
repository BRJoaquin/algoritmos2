#include <string>
#include <iostream>
#include <climits>
#include <cassert>

#define INF INT_MAX;

using namespace std;

// LLPLPPL
// [2,4,5,b,b,b,b] policiasIndex
// [0,1,3,6,b,b,b] ladronesIndex

int policiasYLadrones(string problema, int k)
{
    int capturados = 0;
    int *policias = new int[problema.length()]();
    int policiasLargo = 0;
    int *ladrones = new int[problema.length()]();
    int ladronesLargo = 0;

    for (int i = 0; i < problema.length(); i++)
    {
        char caso = problema[i];
        if (caso == 'P')
        {
            policias[policiasLargo++] = i;
        }
        else
        { // L
            ladrones[ladronesLargo++] = i;
        }
    }

    int policiaActual = 0;
    int ladronActual = 0;

    while (policiaActual < policiasLargo && ladronActual < ladronesLargo)
    {
        // puede ser capturado
        if (abs(policias[policiaActual] - ladrones[ladronActual]) <= k)
        {
            capturados++;
            policiaActual++;
            ladronActual++;
        } else {
            if(policias[policiaActual] > ladrones[ladronActual]) {
                ladronActual++;
            } else {
                policiaActual++;
            }
        }
    }

    return capturados;
}

int main()
{
    string problema;
    int K;
    cin >> problema;
    cin >> K;
    cout << policiasYLadrones(problema, K) << endl;
}