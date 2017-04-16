#ifndef NUM_H
#define NUM_H

#include <iostream>

#include "dbl.h"

class num
{
private:
    intt a;
    dbl b;
public:
    num();
    num(double);
    num(intt,dbl);
    num& operator+ (num&);
    friend std::ostream& operator<< (std::ostream&, num&);
    ~num();
};

#endif // NUM_H
