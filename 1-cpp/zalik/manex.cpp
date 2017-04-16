#include "manex.h"

Manex::Manex() : Man() { }

Manex::Manex(std::string a) : Man(), name(a) { }

Manex::Manex(std::string a, int b) : Man(b), name(a) { }

std::string Manex::getName()
{
    return name;
}

Manex::~Manex() { }
