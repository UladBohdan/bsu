#include <iostream>
#include <string>

using namespace std;

int main()
{
    string w;
    int a[100][3], l[2];
    for (int i=0; i<100; i++)
    {
        a[i][0]=0;
        a[i][1]=0;
        a[i][2]=0;
    }
    for (int i=0; i<2; i++)
    {
        cin >> w;
        for (int k=0; k<w.length(); k++)
        {
            a[k][i]=w[w.length()-1-k]-48;
        }
        l[i]=w.length();
    }
    int t;
    if (l[1]>l[0])
        t=l[1];
    else
        t=l[0];
    for (int i=0; i<t; i++)
    {
        a[i][2]+=a[i][1]+a[i][0];
        if (a[i][2]>9)
        {
            a[i+1][2]++;
            a[i][2]-=10;
        }
    }
    if (a[t][2]!=0)
        t++;
    for (int i=t-1; i>=0; i--)
        cout << a[i][2];
    return 0;
}
