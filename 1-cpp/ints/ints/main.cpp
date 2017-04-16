#include <iostream>

#include "num.h"

using namespace std;

int main()
{
    dbl x;
    try
    {
        x=dbl(150);
    }
    catch (dbl::tooBig obj)
    {
        cout << "TOO BIG: " << obj.value << "  is more than 100" << endl;
    }
    try
    {
        x=dbl(78);
        intt g(197);
        num b(g,x), c(3.08);
        cout << b << " " << c << endl;
        b=b+c;
        cout << b << endl;
        num mas[4];
        mas[0]=num(4.54);
        mas[1]=num(5.11);
        mas[2]=num(9);
        mas[3]=num(9.89);
        cout << mas[1]+mas[2]+mas[3]+mas[0];

    }
    catch (dbl::tooBig obj)
    {
        cout << "TOO BIG: " << obj.value << "  is more than 100" << endl;
    }
    return 0;
}
