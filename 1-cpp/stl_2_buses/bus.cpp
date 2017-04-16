#include "bus.h"

Bus::Bus() { }

Bus::Bus(int a, std::string b, int c, std::string d) : route(a), name(b), num(c), bus(d) { }

std::ifstream& operator>> (std::ifstream& fin, Bus& t)
{
    fin >> t.route >> t.name >> t.num >> t.bus;
    return fin;
}

std::ostream& operator<< (std::ostream& out, Bus& t)
{
    out << t.route << " " << std::setw(10) << t.name << " " << std::setw(2) << t.num << " " << t.bus << std::endl;
    return out;
}

Bus::~Bus() { }
