#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double pi=0, zn=1, t=1, mnl, e;
    cout << "Uviadzice dakladnasc E: ";
    cin >> e;
    do
    {
        mnl=pi;
        pi+=(zn*(4./t));
        zn*=(-1);
        t+=2;
    }
    while (fabs(mnl-pi)>e);
    cout << "Pa formule pi=" << pi;
    return 0;
}
