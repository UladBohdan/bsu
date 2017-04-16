#ifndef BUS_H
#define BUS_H

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

class Bus
{
public:
    int route;
    std::string name;
    int num;
    std::string bus;
    Bus();
    Bus(int, std::string, int, std::string);
    friend std::ifstream& operator>> (std::ifstream&, Bus&);
    friend std::ostream& operator<< (std::ostream&, Bus&);
    ~Bus();
};

#endif // BUS_H
