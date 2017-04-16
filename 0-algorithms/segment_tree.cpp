#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

//ДРЭВА АДЦІНКАЎ (ШУКАЕ МАКС) З АДЗІНОЧНАЙ МАДЫФІКАЦЫЯЙ

using namespace std;

vector <int> tree;
int t, temp; // Budziem sukac max

ifstream fin("input.txt");

int zapoln (int pos)
{
    if (pos>=t)
        return tree[pos];
    tree[pos]=max(zapoln(pos*2),zapoln(pos*2+1));
}

int main()
{
    int n;
    fin >> n;
    t=1<<(int)(log(n)/log(2)+1);
    tree.resize(2*t);
    for (int i=0; i<n; i++)
        fin >> tree[t+i];
    tree[1]=zapoln(1);
    cout << "zaprosy?" << endl;
    int k;
    cin >> k;
    for (int j=0; j<k; j++)
    {
        int mesca, val;
        cout << "!" << endl;
        cin >> mesca >> val;

        mesca+=(t-1);
        tree[mesca]=val;
        mesca/=2;
        while (mesca>0)
        {

            tree[mesca]=max(tree[mesca*2],tree[mesca*2+1]);
            mesca/=2;

        }
        cout << "New tree:" << endl;
        for (int i=1; i<tree.size(); i++)
        {
            cout << tree[i] << " ";
            if (((i+1)&(i))==0)
                cout << endl;
        }
        cout << endl;

    }
    return 0;
}
