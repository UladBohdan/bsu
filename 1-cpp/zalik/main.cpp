#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "manex.h"

using namespace std;

ofstream fout("output");

class comp
{
public:
    bool operator()(Manex* a, Manex* b) const
    {
        return (a->getName() < b->getName());
    }
};

int main()
{
    Man a, b(1985);
    Manex c("Hellozz",2000), d("Hellozz"), e("smth",1990);
    string x;
    Man *p[5]={&a,&d,&c,&b,&e};
    vector <Manex*> derv;
    for (int i=0; i<5; i++)
        if (dynamic_cast<Manex*>(p[i]))
            derv.push_back(dynamic_cast<Manex*>(p[i]));
    cout << "Number of derivative objects: " << derv.size() << endl;
    fout << "Number of derivative objects: " << derv.size() << endl;
    sort(derv.begin(), derv.end(),comp());
    cout << "Sorted array: ";
    fout << "Sorted array: ";
    for (unsigned int i=0; i<derv.size(); i++)
    {
        cout << derv[i]->getName() << " ";
        fout << derv[i]->getName() << " ";
    }
    int temp=1;
    for (unsigned int i=1; i<derv.size(); i++)
           if (derv[i]->getName()!=derv[i-1]->getName())
               temp++;
    cout << endl << "Number of different names: " << temp << endl << endl;
    fout << endl << "Number of different names: " << temp << endl;
    return 0;
}
