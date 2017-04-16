#include <iostream>
#include <algorithm>
#include <vector>

#include "lefthand.h"
#include "righthand.h"

using namespace std;

class comp
{
public:
    bool operator()(base* a, base* b) const
    {
        return (a->value() < b->value());
    }
};

int main()
{
    lefthand a1, a2(8), a3(10), a4(909);
    righthand b1, b2(23), b3(11), b4(10);
    base* p[]={&a1, &a2, &a3, &a4, &b1, &b2, &b3, &b4};
    sort(p,p+8,comp());
    cout << "Sorted:  ";
    for (int i=0; i<8; i++)
        cout << p[i]->value() << " ";
    cout << endl;
    vector <base*> v1, v2;
    for (int i=0; i<8; i++)
    {
        if (!dynamic_cast<righthand*>(p[i]))
            v1.push_back(p[i]);
        else
            v2.push_back(p[i]);
    }
    cout << "Pairs: " << endl;
    for (unsigned int i=0; i<v1.size(); i++)
    {
        cout << v1[i]->value() << " " << v2[i]->value() << endl;
    }
    return 0;
}

