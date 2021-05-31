#include <cassert>
#include <string>
#include <iostream>
using namespace std;

int combinatoria(int n, int p) {
    int ** m =  new int*[n+1];
    for(int i = 0 ; i < n+1; i++) {
        m[i] = new int[p+1];
    }

    for(int i = 0 ; i < n+1; i++) {
        for(int j = 0 ; j < p+1; j++) {
            if(j > i) {
                m[i][j] = 0;
            }else if(i == j || j == 0) {
                m[i][j] = 1;
            }else {
                m[i][j] = m[i-1][j] + m[i-1][j-1];
            }
        }
    }
    return m[n][p];
}


int main () 
{
    int N;
    int P;
    cin >> N;
    cin >> P;
    cout << combinatoria(N,P) << endl;
    return 0;
}