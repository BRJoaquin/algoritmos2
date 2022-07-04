#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

long padovan_memo(unsigned int n, long* memo) {
    if(n <= 2)
    return 1;

    if(memo[n] == 0) {
        memo[n] = padovan_memo(n-2, memo) + padovan_memo(n-3, memo);
    }
    return memo[n];
}

long padovan(unsigned int n) {
    long *memo = new long[n+1]();
    return padovan_memo(n, memo);
}

int main()
{
    cout << padovan(5) << endl;
    return 0;
}