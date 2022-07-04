#include <cassert>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

long padovan(unsigned int n) {
    long *memo = new long[n+1]();
    memo[0] = 1;
    memo[1] = 1;
    memo[2] = 1;
    for (int i = 3; i <= n; i++)
    {
        memo[i] = memo[i-2] + memo[i-3];
    }
    return memo[n];
}

int main()
{
    cout << padovan(5) << endl;
    return 0;
}