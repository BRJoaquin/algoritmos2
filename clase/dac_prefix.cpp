#include <string>
#include <iostream>
#include <climits>
#include <cassert>


using namespace std;

string prefixStr(string pal1, string pal2) {
    string ret = "";
    int l1 = pal1.length();
    int l2 = pal2.length();
    int min = l1 < l2 ? l1 : l2;

    for (int i = 0; i < min; i++)
    {
        if(pal1[i] == pal2[i]) {
            ret += pal1[i];
        } else {
            break;
        }
    }
    return ret;
}


string prefix(string * palabras, int i, int f) {
    // caso base
    if(i == f) {
        return palabras[i];
    }

    // dividir
    int mitad = ((f - i) / 2) + i;

    // conquista
    string prefixIzq = prefix(palabras, i, mitad);
    string prefixDer = prefix(palabras, mitad + 1, f);

    // merge
    return prefixStr(prefixIzq, prefixDer);
}


int main()
{
// ["flower", "flow", "flight"]
    string * palabras = new string[3]();
    palabras[0] = "flower";
    palabras[1] = "flow";
    palabras[2] = "floight";

    cout << prefix(palabras, 0, 2) << endl;
}