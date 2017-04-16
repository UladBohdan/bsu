#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// All permutations of N elements
// Two neighbor permutations differs with just one transposition
// SHEN     2.5.2

int main()
{
    const int n=4;
    int x[n], y[n], d[n], inv_x[n];
    // inv_x    :   returns zero-based position of (i+1)   :   inv_x[0] - position of 1
    for (int i=0; i<n; i++)
    {
        x[i]=n-i;
        inv_x[i]=n-i-1;
        y[i]=0;
        d[i]=1;
    }
    int s=1;
    for (int i=2; i<=n; i++)
        s*=i;
    for (int i=0; i<s; i++)
    {
        for (int j=0; j<n; j++)
            cout << x[j] << " ";
        cout << endl;
        int t=n-1;
        while ( (y[t]==t && d[t]==1) || (y[t]==0 && d[t]==-1) )
            t--;
        y[t]+=d[t];
        for (int j=t+1; j<n; j++)
            d[j]*=(-1);
        int pos1, pos2, val1, val2;
        pos1=inv_x[t];
        pos2=pos1+d[t];
        val1=t;
        val2=x[pos2]-1;
        swap(x[pos1],x[pos2]);
        swap(inv_x[val1],inv_x[val2]);
    }
    return 0;
}
