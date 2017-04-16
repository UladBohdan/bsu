#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <queue>

using namespace std;

// SORT FOR O(K*N)
// SHEN 4.4.4

int main()
{
    srand(time(NULL));
    const int k=5, n=10;
    int temp=2, a[n];
    for (int i=1; i<k; i++)
        temp*=2;
    for (int i=0; i<n; i++)
        a[i]=rand()%temp;
    cout << " ARRAY: ";
    for (int i=0; i<n; i++)
        cout << a[i] << " ";
    cout << endl;

    for (int i=0; i<k; i++)
    {
        queue <int> q[2];
        for (int j=0; j<n; j++)
            q[ (a[j]>>i) & 1 ].push(a[j]);
        int pos=0;
        while (!q[0].empty())
        {
            a[pos++]=q[0].front();
            q[0].pop();
        }
        while (!q[1].empty())
        {
            a[pos++]=q[1].front();
            q[1].pop();
        }
    }

    cout << "SORTED: ";
    for (int i=0; i<n; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
