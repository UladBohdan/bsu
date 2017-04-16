#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

//search element in sorted table for O(n+m)

int main()
{
    const int n=5, m=10;

    srand(time(NULL));
    int a[n][m];
    a[0][0]=1;
    for (int i=1; i<n; i++)
        a[i][0]=a[i-1][0]+rand()%2;
    for (int i=1; i<m; i++)
        a[0][i]=a[0][i-1]+rand()%2;
    for (int i=1; i<n; i++)
        for (int j=1; j<m; j++)
            a[i][j]=a[i-1][j]+a[i][j-1]+rand()%2;
    cout << "matrix: " << endl;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
            cout << a[i][j] << '\t';
        cout << endl;
    }
    cout << "what are we looking for: ";
    int q;
    cin >> q;
    if (q<a[0][0] || q>a[n-1][m-1])
    {
        cout << "N/A" << endl;
        return 0;
    }
    int l=n-1, k=0;
    while (l>=1 && k<m-1)
    {
        int t1=l, t2=k;
        if (a[l][k]<q)
            k++;
        if (a[l][k]>q)
            l--;
        if (t1==l && t2==k)
            break;
    }
    if (a[l][k]!=q)
        cout << "N/A" << endl;
    else
        cout << "Found! row " << l+1 << " col " << k+1 << endl;
    return 0;
}
