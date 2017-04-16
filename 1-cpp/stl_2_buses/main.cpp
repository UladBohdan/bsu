#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <utility>
#include <numeric>

#include "bus.h"

using namespace std;

string brand;

bool bynum (Bus a, Bus b)
{
    return (a.num<b.num);
}

void out_brand (Bus a)
{
    if (a.bus==brand)
        cout << "  " << a;
}

int main()
{
    ifstream fin("buses");
    vector <Bus> v;
    Bus temp;
    while (!fin.eof())
    {
        fin >> temp;
        v.push_back(temp);
    }
    v.pop_back();
    sort(v.begin(), v.end(), bynum);
    cout << "BUSES SORTED BY NUMBER: " << endl;
    for (unsigned int i=0; i<v.size(); i++)
        cout << "  " << v[i];
    multimap <int, Bus> m;
    for (unsigned int i=0; i<v.size(); i++)
        m.insert(pair<int,Bus>(v[i].route,v[i]));
    int r;
    cout << endl << "Enter a route: ";
    cin >> r;
    cout << endl << "BUSES OF " << r << " ROUTE:" << endl;
    for (multimap<int,Bus>::iterator i=m.begin(); i!=m.end(); i++)
        if (i->first==r)
            cout << "  " << i->second;
    cout << endl << "Changing a driver (input two surnames): ";
    string dr1, dr2;
    cin >> dr1 >> dr2;
    for (multimap<int,Bus>::iterator i=m.begin(); i!=m.end(); i++)
        if ((i->second).name==dr1)
            (i->second).name=dr2;
    cout << endl << "NEW LIST OF BUSES: " << endl;
    for (multimap<int,Bus>::iterator i=m.begin(); i!=m.end(); i++)
        cout << "  " << i->second;
    cout << endl << "Enter a brand of bus: ";
    cin >> brand;
    cout << endl << "ROUTES WITH THIS BRAND OF BUS: " << endl;
    for_each(v.begin(),v.end(),out_brand);
    string* arr = new string[v.size()];
    for (vector<Bus>::iterator i=v.begin(); i!=v.end(); i++)
        arr[i-v.begin()]=i->bus;
    set <string> s (arr,arr+v.size());
    cout << endl << "UNIQUE BRANDS OF BUSES: " << endl;
    for (set<string>::iterator i=s.begin(); i!=s.end(); i++)
        cout << "  " << *i << endl;
    return 0;
}
