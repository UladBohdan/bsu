#include <iostream>

using namespace std;

// All the positions of N QUEENS on NxN board, when no one hits another one
// Algorithm based on BACK_TRACKING. We go throung the tree
// SHEN     3.1.1

const int n=5;
int a[n][n]={}, k=n;

void out();

bool isFine()
{
    for (int j=0; j<n; j++)
    {
        int s=0;
        for (int i=0; i<n; i++)
            s+=a[i][j];
        if (s>1)
            return false;
    }
    for (int s=0; s<2*n-1; s++)
    {
        int temp=0;
        for (int i=0; i<n; i++)
        {
            int j=s-i;
            if (j>=0 && j<n)
                temp+=a[i][j];
        }
        if (temp>1)
            return false;
    }
    for (int s=-(n-1); s<n; s++)
    {
        int temp=0;
        for (int i=0; i<n; i++)
        {
            int j=i-s;
            if (j>=0 && j<n)
                temp+=a[i][j];
        }
        if (temp>1)
            return false;
    }
    if (k==0)
        out();
    return true;
}

void out()
{
    cout << endl;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

void up_up()
{
    if (k==0)
    {
        isFine();
        return;
    }
    while(k>0 && isFine())
    {
        a[k-1][0]=1;
        k--;
    }
    if (k==0)
        isFine();
    return;
}

bool exists_right()
{
    return !(a[k][n-1]);
}

void go_right()
{
    for (int i=0; i<n; i++)
        if (a[k][i]==1)
        {
            a[k][i]=0;
            a[k][i+1]=1;
            return;
        }
    return;
}

void go_down()
{
    for (int i=0; i<n; i++)
        a[k][i]=0;
    k++;
    return;
}

int main()
{
    up_up();
    while (k!=n)
    {
        if (exists_right())
        {
            go_right();
            up_up();
        }
        else
            go_down();
    }
    return 0;
}
