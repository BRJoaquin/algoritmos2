#include <cassert>
#include <string>
#include <iostream>
using namespace std;

/* 
CB: sum(1) = 1
PR: sum(n) = n + sum(n-1)
*/

int sum(int n) {
    if(n == 1)
        return n;
    return n + sum(n-1);
}

int sumPD(int n) {
    int * res = new int[n+1];
    res[1] = 1;
    for (int i = 2; i <= n; i++)
        res[i] = i + res[i-1];
    return res[n];
}


int main () 
{
    int N;
    cin >> N;
    cout << sum(N) << endl;
    cout << sumPD(N) << endl;
    return 0;
}