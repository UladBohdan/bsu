#include "num.h"

num::num() : a(0), b(0) { }

num::num(double x) : a((int)x), b((int)(x*100)%100) { }

num::num(intt x, dbl y) : a(x), b(y) { }

num& num::operator+ (num& x)
{
    int t1=(int)(x.a)+(int)(a);
    int t2=(int)(x.b)+(int)(b);
    if (t2>100)
    {
        t1++;
        t2-=100;
    }
    num* temp = new num((double)(t1*1.+t2*0.01));
    return *temp;
}

std::ostream& operator<< (std::ostream& os, num& x)
{
    if ((int)x.b<10)
        os << (int)(x.a) << ".0" << (int)(x.b);
    else
        os << (int)(x.a) << "." << (int)(x.b);
    return os;
}

num::~num() { }
