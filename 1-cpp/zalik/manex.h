#ifndef MANEX_H
#define MANEX_H

#include "man.h"

class Manex : public Man
{
public:
    Manex();
    Manex(std::string);
    Manex(std::string, int);
    std::string getName();
    ~Manex();
private:
    std::string name;
};

#endif // MANEX_H
