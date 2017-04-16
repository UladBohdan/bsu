#include "dbl.h"

dbl::dbl() : intt() { }

dbl::dbl(int x)
{
    x<100 ? value=x : throw tooBig(x);
}

dbl::dbl(dbl& x) : intt(x.value) { }

dbl& dbl::operator+(const dbl& x)
{
    dbl* temp = new dbl(value+x.value);
    return *temp;
}

dbl::operator int()
{
    return value;
}

dbl& dbl::operator=(const dbl& x)
{
    value=x.value;
    return *this;
}

dbl::~dbl() { }
