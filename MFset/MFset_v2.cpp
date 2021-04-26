#include <iostream>
using namespace std;
class MFSet
{
	int *altura, *parent, n;

public:
	MFSet(int n)
	{
		parent = new int[n];
		altura = new int[n];
		this->n = n;
		makeSet();
	}

	void makeSet()
	{
		for (int i = 0; i < n; i++)
		{
			parent[i] = i;
		}
	}

	int find(int x)
	{
		if (parent[x] != x)
		{
			// aplanamos el arbol
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	void merge(int x, int y)
	{
		int xset = find(x);
		int yset = find(y);

		// si estan dentro del mismo set terminamos
		if (xset == yset)
			return;

		// evitamos aumentar la altura del arbol
		if (altura[xset] < altura[yset])
		{
			parent[xset] = yset;
		}
		else if (altura[xset] > altura[yset])
		{
			parent[yset] = xset;
		}

		// si ambas alturas con la misma usamos cualquiera y actualizamos la altura
		else
		{
			parent[yset] = xset;
			altura[xset] = altura[xset] + 1;
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