#include "intt.h"

intt::intt() : value(0) { }

intt::intt(int x) : value(x) { }

intt::intt(intt& x) : value(x.value) { }

intt& intt::operator+ (const intt& x)
{
    intt* temp = new intt(value+x.value);
    return *temp;
}

intt::operator int()
{
    return value;
}

intt& intt::operator= (const intt& x)
{
    value=x.value;
    return *this;
}

intt::~intt() { }
