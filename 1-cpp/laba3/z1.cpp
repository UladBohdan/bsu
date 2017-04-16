#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Uviadzice X i E: ";
    double x, ans=0, mnl, e;
    int prev=1, last=2;
    cin >> x >> e;
    double ch=x, zn=1;
    do
    {
        mnl=ans;
        ans+=(prev*ch/zn);
        prev*=(-1);
        ch*=(x*x);
        zn*=last;
        zn*=(last+1);
        last+=2;
    }
    while (fabs(mnl-ans)>e);
    cout << "sin pa nasaj formulie: " << ans << endl;
    cout << "sin z cmath: " << sin(x);
    return 0;
}
