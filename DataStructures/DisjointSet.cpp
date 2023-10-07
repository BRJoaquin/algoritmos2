#ifndef DISJOINT_SET
#define DISJOINT_SET

class DisjointSet
{
private:
    int *parent;
    int *heigth;
    int size;

public:
    DisjointSet(int n) {
        this->size = n;
        this->parent = new int[n + 1];
        this->heigth = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            this->parent[i] = i;
            this->heigth[i] = 0;
        }
    }

    int find(int x) {
        if (this->parent[x] == x) {
            return x;
        }
        // Path compression
        this->parent[x] = find(this->parent[x]);
        return this->parent[x];
    }

    void merge(int x, int y) {
        int xRoot = find(x);
        int yRoot = find(y);
        // if they are already in the same set
        if (xRoot == yRoot) {
            return;
        }
        
        if (this->heigth[xRoot] < this->heigth[yRoot]) {
            // if x's tree is less than y's tree
            this->parent[xRoot] = yRoot;
        } else if (this->heigth[xRoot] > this->heigth[yRoot]) {
            // if x's tree is greater than y's tree
            this->parent[yRoot] = xRoot;
        } else {
            // if x's tree is equal to y's tree
            this->parent[yRoot] = xRoot;
            // increase the heigth of x's tree
            this->heigth[xRoot]++;
        }
    }
};
#endif