#ifndef DBL_H
#define DBL_H

#include "intt.h"

class dbl : public intt
{
public:
    dbl();
    dbl(int);
    dbl(dbl&);
    class tooBig
    {
    public:
        int value;
        tooBig(int x) : value(x) { }
    };
    dbl& operator+(const dbl&);
    operator int();
    dbl& operator=(const dbl&);
    ~dbl();
};

#endif // DBL_H
