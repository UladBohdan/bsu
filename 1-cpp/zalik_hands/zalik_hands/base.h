#ifndef BASE_H
#define BASE_H

class base
{
protected:
    int n;
public:
    base();
    base(int);
    int value();
    virtual void abstr()=0;
    virtual ~base();
};

#endif // BASE_H
