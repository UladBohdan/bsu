//Counts the n-th fibonacci number (long arifmetics)

#include <iostream>

using namespace std;

int main()
{
    int n, a[1000][3], l[2], t;
    cout << "Vvedite n>0 (pomnite, pri n=1 f=1, pri n=2 f=1)" << endl;
    cin >> n;
    if ((n==1)||(n==2))
    {
        cout << 1;
        return 0;
    }
    if (n==3)
    {
        cout << 2;
        return 0;
    }
    for (int k=0; k<1000; k++)
    {
        a[k][0]=0;
        a[k][1]=0;
        a[k][2]=0;
    }
    a[0][0]=1;
    a[0][1]=2;
    l[0]=1;
    l[1]=1;
    for (int i=1; i<n-2; i++)
    {
        if (l[1]>l[0])
            t=l[1];
        else
            t=l[0];
        for (int k=0; k<t; k++)
        {
            a[k][2]+=a[k][1]+a[k][0];
            if (a[k][2]>9)
            {
                a[k+1][2]++;
                a[k][2]-=10;
            }
        }
        if (a[t][2]!=0)
            t++;
        for (int k=0; k<1000; k++)
            a[k][0]=a[k][1];
        l[0]=l[1];
        for (int k=0; k<1000; k++)
            a[k][1]=a[k][2];
        l[1]=t;
        for (int k=0; k<1000; k++)
            a[k][2]=0;
    }
    for (int k=t-1; k>=0; k--)
            cout << a[k][1];
    return 0;
}
