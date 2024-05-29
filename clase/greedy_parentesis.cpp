#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

int parentesis(string &parentesis)
{
    int cantidadDeCambios = 0;
    int balance = 0;
    int j = parentesis.size() - 1;
    for (int i = 0; i < parentesis.size(); i++)
    {
        if (parentesis[i] == '[')
        {
            balance++;
        }
        else
        {
            balance--;
        }
        if (balance < 0)
        {
            cantidadDeCambios++;
            while (parentesis[j] != '[')
            {
                j--;
            }
            swap(parentesis[i], parentesis[j]);
            balance = 1;
        }
    }

    return cantidadDeCambios;
}

int main()
{
    string parentesis1 = "[[][]]][";       // Tiene que devolver 1
    string parentesis1 = "[[][]][]";       // Tiene que devolver 1

    string parentesis2 = "[][[][[]]]]][["; // Tiene que devolver 1
    string parentesis2 = "[][[][[]]][][]"; // Tiene que devolver 1

    string parentesis3 = "]]][[[";
    string parentesis3 = "[][[]]";


    cout << parentesis(parentesis1) << " - " << parentesis1 <<   endl;
    cout << parentesis(parentesis2) << " - " << parentesis2 <<  endl;
    cout << parentesis(parentesis3) << " - " << parentesis3 <<  endl;
}