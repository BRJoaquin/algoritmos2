#include <string>
#include <iostream>
using namespace std;

int f(unsigned int a, unsigned int b)
{
    if (a == 0 || b == 0)
    {
        return 1;
    }
    if (a > b)
    {
        return a;
    }
    return f(b - a, b - 1) + f(a - 1, b);
}

// Utilizo memoizacion ya que no es posible usar tabulacion debido a que 
// 
int f_memo(unsigned int a, unsigned int b, int **calculados)
{
    if (a == 0 || b == 0)
    {
        return 1;
    }
    if (a > b)
    {
        return a;
    }
    if (calculados[a][b] == -1)
    {
        calculados[a][b] = f_memo(b - a, b - 1, calculados) + f_memo(a - 1, b, calculados);
    }
    return calculados[a][b];
}

int main()
{
    int a;
    int b;
    cin >> a;
    cin >> b;
    cout << f(a, b) << endl;
    // necesito el maximo debido a que se nos puede ir de rango
    int max = a > b ? a : b;
    int **calculados = new int *[max + 1];
    for (int i = 0; i < max + 1; i++)
    {
        calculados[i] = new int[max + 1]();
        for (int j = 0; j < max + 1; j++)
        {
            calculados[i][j] = -1;
        }
    }
    cout << f_memo(5, 8, calculados) << endl;
    return 0;
}