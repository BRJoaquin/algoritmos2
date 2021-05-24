#include <iostream>
#include <limits.h>
#include <cassert>
#include <string.h>
using namespace std;

void intercambiar(char p[], int i, int j)
{
    char aux = p[i];
    p[i] = p[j];
    p[j] = aux;
}

void minIntercambios(char p[], int n)
{
    // for (int i = 0; i < n; i++)
    // {
    //     cout << p[i];
    // }
    cout << endl;
    int intercambios = 0;
    int balance = 0;
    for (int i = 0; i < n; i++)
    {
        if (p[i] == '[')
        {
            balance++;
        }
        else
        {
            balance--;
        }

        if (balance == -1)
        {
            bool encontreSustituto = false;
            int posSustituto;
            for (int j = i + 1; j < n && !encontreSustituto; j++)
            {
                if (p[j] == '[') {
                    encontreSustituto = true;;
                    posSustituto = j;
                }
            }
            intercambiar(p, i, posSustituto);
            intercambios++;
            balance = 1;
        }
    }

    cout << "Cantidad de intercambios " << intercambios << endl;
    for (int i = 0; i < n; i++)
    {
        cout << p[i];
    }
    cout << endl;
}

int main()
{
    char parentesis[14] = {'[', ']', '[', '[', ']', '[', '[', ']', ']', ']', ']', ']', '[', '['};
    minIntercambios(parentesis, 14);
    // char parentesis[6] = {']', ']', ']', '[', '[', '['};
    // minIntercambios(parentesis, 6);
    return 0;
}