#ifndef INTT_H
#define INTT_H

class intt
{
protected:
    int value;
public:
    intt();
    intt(int);
    intt(intt&);
    intt& operator+(const intt&);
    operator int();
    intt& operator=(const intt&);
    ~intt();
};

#endif // INTT_H
