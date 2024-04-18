#include <string>
#include <iostream>
#include <climits>
using namespace std;


class MFSet {
    private:
        int* sigoA;
        int* altura;
        int N;
    public:
        MFSet(int _N) {
            this->N = _N;
            sigoA = new int[_N]();
            altura = new int[_N]();
            for (int i = 0; i < _N; i++)
            {
                sigoA[i] = -1;
                altura[i] = 1;
            }
        }

        int find(int el) {
            if(sigoA[el] == -1) {
                return el;
            }
            // path compression
            sigoA[el] = find(sigoA[el]);
            return sigoA[el];
        }

        void merge(int el1, int el2) {
            int lider1 = find(el1);
            int lider2 = find(el2);
            
            if(lider1 != lider2) {
                // union by rank
                if(altura[lider1] < altura[lider2]) {
                    sigoA[lider1] = lider2;
                } else if(altura[lider1] > altura[lider2]) {
                    sigoA[lider2] = lider1;
                } else { // misma altura
                    sigoA[lider1] = lider2;
                    altura[lider2]++;
                }
            }
        }
};

// int main()
// {
//     MFSet * grupito = new MFSet(5);

//     grupito->merge(0, 1);
//     grupito->merge(2, 4);
//     grupito->merge(0, 3);
//     grupito->merge(3, 4);
//     grupito->merge(2, 4);

//     if (grupito->find(0) == grupito->find(4))
//     {
//         std::cout << "Estan en el mismos grupito!" << std::endl;
//     }else {
//         std::cout << "No estan el mismo grupito :(" << std::endl;
//     }
    
// }