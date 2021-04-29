#include <iostream>
using namespace std;
class MFSet
{
    int *parent, n;

public:
    MFSet(int n)
    {
        parent = new int[n];
        this->n = n;
        makeSet();
    }

    void makeSet()
    {
        for (int i = 0; i < n; i++)
        {
            // yo me represento a mi mismo
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            return find(parent[x]);
        }
        return parent[x];
    }

    void merge(int x, int y)
    {
        int xset = find(x);
        int yset = find(y);

        // si no estan dentro del mismo set los unimos
        if (xset != yset)
        {
            parent[yset] = xset;
        }
    }
};

int main()
{
    MFSet mfset(5);
    mfset.merge(0, 2);
    mfset.merge(4, 2);
    mfset.merge(3, 1);
    if (mfset.find(4) == mfset.find(0))
        cout << "Si\n";
    else
        cout << "No\n";

    if (mfset.find(1) == mfset.find(0))
        cout << "Si\n";
    else
        cout << "No\n";

    return 0;
}
// fuente: https://www.geeksforgeeks.org/disjoint-set-data-structures/