#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Gives all permutations of set of N elements

void my_next_permutation(int* a, int n)
{
    int t=n-1;
    while (t>0 && a[t-1]>a[t])
        t--;
    t--;
    int r=n-1;
    while (a[r]<a[t])
        r--;
    swap(a[r],a[t]);
    r=n-1;
    t++;
    while (t<r)
    {
        swap(a[t],a[r]);
        t++;
        r--;
    }
    return;
}

int main()
{
    const int n=4; // k - length, 1..n - values
    int a[n];
    for (int i=0; i<n; i++)
        a[i]=i+1;
    int s=1;
    for (int i=2; i<=n; i++)
        s*=i;
    for (int i=0; i<s; i++)
    {
        for (int j=0; j<n; j++)
            cout << a[j] << " ";
        cout << endl;
        my_next_permutation(a,n);
    }
    return 0;
}
