#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

// MERGE SORT

void merge(int a[], int p, int q, int r)
{
    int p0=p, q0=q;
    int* b = new int[r-p];
    for (int i=0; i<r-p; i++)
    {
        if (p0!=q && q0!=r)
            a[p0]<=a[q0] ? b[i]=a[p0++] : b[i]=a[q0++];
        else if (p0==q)
            b[i]=a[q0++];
        else
            b[i]=a[p0++];
    }
    for (int i=0; i<r-p; i++)
        a[i+p]=b[i];
    delete[] b;
    return;
}

int main()
{
    const int n=8;
    int a[n];
    srand(time(NULL));
    for (int i=0; i<n; i++)
        a[i]=rand()%15;
    cout << " ARRAY: ";
    for (int i=0; i<n; i++)
        cout << a[i] << " ";
    cout << endl;
    int k=1;
    while (k<n)
    {
        int p=0;
        while (p+k<n)
        {
            merge(a,p,p+k,min(p+2*k,n));
            p+=2*k;
        }
        k*=2;
    }
    cout << "SORTED: ";
    for (int i=0; i<n; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
