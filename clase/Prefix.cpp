#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

string prefixComun(string pal1, string pal2) {
    int l1 = pal1.length();
    int l2 = pal2.length();

    string prefix = "";

    int min =  l1 < l2 ? l1 : l2;

    for(int i = 0; i < min; i++) {
        if(pal1[i] == pal2[i]){
            prefix += pal1[i];
        }else{
            break;
        }
    }
    return prefix;
}

string prefix(string* palabras, int i, int f) {
    if(i == f) {
        return palabras[i];
    }

    int mitad = (i+f)/2;

    string prefix1 = prefix(palabras, i , mitad);
    string prefix2 = prefix(palabras, mitad + 1 , f);

    return prefixComun(prefix1, prefix2);
}



int main()
{
  string  * palabras = new string[4];
  palabras[0] = "flower";
  palabras[1] = "flow";
  palabras[2] = "flight";
  palabras[3] = "floyd";

  string prefixComun = prefix(palabras, 0, 3);
  cout << prefixComun << endl;
}