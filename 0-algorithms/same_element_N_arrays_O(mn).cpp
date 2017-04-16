#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Looks for same elements in n arrays (size m each)
//Works for O(n*m)

int main()
{
    const int n=5, m=10; // n - number of arrays, m - size of a[i][j]

    srand(time(NULL));
    int a[n][m];
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            a[i][j]=rand()%10;
    for (int i=0; i<n; i++)
        sort(a[i],a[i]+m);
    for (int i=0; i<n; i++)
    {
        cout << "Array " << i << " : ";
        for (int j=0; j<m; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    int b[n]={}, x[n]={}, t;
    x[0]=1;
    for (; b[0]<m; b[0]++)
    {
        t=1;
        for (int j=1; j<n; j++)
        {
            if (a[j][b[j]]==a[j-1][b[j-1]])
                x[j]=1;
            while (b[j]+1<m && a[j][b[j]+1]<=a[j-1][b[j-1]])
            {
                x[j]=1;
                b[j]++;
            }
            t*=x[j];
        }
        if (t && a[n-1][b[n-1]]==a[0][b[0]])
        {
            cout << "Yeah! common value is " << a[0][b[0]] << endl;
            return 0;
        }
    }
    cout << "NOT EXIST" << endl;
    return 0;
}
