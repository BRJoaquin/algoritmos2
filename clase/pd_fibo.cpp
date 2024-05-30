#include <string>
#include <iostream>
#include <climits>
#include <cassert>
using namespace std;

long fibonacci_memo(int n, int* memo) {
    if (n <= 1) return n;
    if(memo[n] != -1) return memo[n];
    memo[n] = fibonacci_memo(n-1, memo) + fibonacci_memo(n-2, memo);
    return memo[n];
}


int main()
{
    int n;
    cin >> n;
    int* memo = new int[n+1]();
    for (int i = 0; i <= n; i++)
    {
        memo[i] = -1;
    }
    
    cout << fibonacci_memo(n, memo) << endl;
    return 0;
}