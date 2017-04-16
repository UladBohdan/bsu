#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

//Length of the longest common subsequance of two arrays
//O(n*m)

using namespace std;

int f(int* a, int n, int* b, int m)
{
    if (n==0 || m==0)
        return 0;
    if (a[n-1]==b[m-1])
        return f(a,n-1,b,m-1)+1;
    else
        return max(f(a,n-1,b,m),f(a,n,b,m-1));
}

int main()
{
    const int n=5, m=5;
    int a[n], b[m];
    srand(time(NULL));
    for (int i=0; i<n; i++)
    {
        a[i]=rand()%10;
        cout << a[i] << " ";
    }
    cout << endl;
    for (int i=0; i<m; i++)
    {
        b[i]=rand()%10;
        cout << b[i] << " ";
    }
    cout << endl;
    cout << "length of max subsequence " << f(a,n,b,m) << endl;
    return 0;
}
