#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

// BINARY TREE SORT
// Time complexity O(N*logN)
// Memory: N (no any additional memory)

const int n=10;
int a[n];
int k=n-1;

void update(int rt)
{
    while ( (2*rt+1<=k && a[2*rt+1]>=a[rt]) || (2*rt+2<=k && a[2*rt+2]>=a[rt]) )
    {
        if (2*rt+2<=k)
        {
            if (a[2*rt+2]>a[2*rt+1])
            {
                swap(a[rt],a[2*rt+2]);
                rt=2*rt+2;
            }
            else
            {
                swap(a[rt],a[2*rt+1]);
                rt=2*rt+1;
            }
        }
        else
        {
            swap(a[rt],a[2*rt+1]);
            rt=2*rt+1;
        }
    }
    return;
}

int main()
{
    srand(time(NULL));
    for (int i=0; i<n; i++)
        a[i]=rand()%15;
    cout << " ARRAY: ";
    for (int i=0; i<n; i++)
        cout << a[i] << " ";
    cout << endl;

    for (int i=n-1; i>=0; i--)
        update(i);
    while (k>0)
    {
        swap(a[0],a[k]);
        k--;
        update(0);
    }

    cout << "SORTED: ";
    for (int i=0; i<n; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
