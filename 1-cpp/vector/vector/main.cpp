#include <iostream>

#include "vector.h"
#include "vectorex.h"

using namespace std;

int main()
{
    int d[5]={7,6,5,4,3};
    vector <int> a(d, 4);
    cout << a.size() << " " << a.begin() << endl;
    a.push_back(9);
    a.push_back(15);
    cout << a.size() << " " << a.begin() << endl;
    a.pop_back();
    cout << a.size() << " " << a.begin() << endl;
    for (int i=0; i<a.size(); i++)
        cout << a[i] << " ";
    cout << endl;

    vectorex <double> b(3);
    b.push_back(7.8);
    for (int i=0; i<b.size(); i++)
        cout << b[i] << " ";
    cout << endl;

    b.push_front(0.1);
    double* place;
    place=b.begin();
    while (place!=b.end())
        cout << *place++ << " ";
    cout << endl;
    return 0;
}
