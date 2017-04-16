#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Gives all subsets with length K from set with N elements

int c(int n, int k)
{
    int ans=1;
    for (int i=1; i<=n; i++)
        ans*=i;
    for (int i=1; i<=n-k; i++)
        ans/=i;
    for (int i=1; i<=k; i++)
        ans/=i;
    return ans;
}

int main()
{
    const int n=5, k=5;
    int a[n]={}, b[n];
    for (int i=n-k; i<n; i++)
        a[i]=1;
    srand(time(NULL));
    for (int i=1; i<=n; i++)
        b[i-1]=i;
    for (int i=0; i<c(n,k); i++)
    {
        for (int j=0; j<n; j++)
            if (a[j])
                cout << b[j] << " ";
        cout << endl;
        int t=n-1;
        while (t>0 && a[t-1]>=a[t])
            t--;
        swap(a[t-1],a[t]);
    }
    return 0;
}
