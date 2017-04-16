#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

//All the possibilities to connect 2*n points on a circle with N chors which not cross each other
//Modification of all Catalan sequences
// SHEN     2.6.3

bool last (int* a, int n)
{
    for (int i=n; i<2*n; i++)
        if (a[i]!=-1)
            return false;
    return true;
}

int main()
{
    const int n=3;
    int a[2*n];
    for (int i=0; i<2*n; i+=2)
    {
        a[i]=1;
        a[i+1]=-1;
    }
    while (true)
    {
        bool tobreak=last(a,n);
        stack <int> st;
        for (int j=0; j<2*n; j++)
        {
            if (a[j]==1)
            {
                st.push(j+1);
            }
            else
            {
                cout << " " << st.top() << "<->" << j+1 << " ";
                st.pop();
            }
        }
        cout << endl;
        int t=2*n-1, s=0;
        while (t>0 && a[t]==-1)
        {
            s++;
            t--;
        }
        while (t>0 && a[t]==1)
        {
            s--;
            t--;
        }
        a[t]=1;
        s+=2;
        for (int j=t+1; j<2*n-1; j++)
        {
            if (s>0)
            {
                a[j]=-1;
                s--;
            }
            else
            {
                a[j]=1;
                s++;
            }
        }
        if (tobreak)
            break;
    }
    return 0;
}
