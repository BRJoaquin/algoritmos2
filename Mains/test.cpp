#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;
int main()
{
    int A;
    cin >> A;
    string N;
    int K;
    string arr[A];
    for (int i = 0; i < A; i++)
    {
        N = "";
        cin >> N;
        cin >> K;
        int suma = 0;
        for (int j = 0; j < K; j++)
        {
            int aux;
            cin >> aux;
            suma += aux;
        }
        arr[i] = N + " " + to_string(suma / K);
    }
    cout << endl << endl << "Imprimiendo resultados:" << endl;
    for (int i = 0; i < A; i++)
    {
        cout << arr[i] << endl;
    }
}