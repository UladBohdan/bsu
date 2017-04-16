#include "bits.h"

void bits::push(int a)
{
    data[a/64]|=((unsigned long int)(1)<<(63-a%64));
}

void bits::pop(int a)
{
    if (find(a))
        data[a/64]^=((unsigned long int)(1)<<(63-a%64));
}

bool bits::find(int a)
{
    return ((data[a/64]>>(63-a%64))&(1));
}

int* bits::out()
{
    vector <int> values;
    for (int i=0; i<256; i++)
        if (find(i))
            values.push_back(i);
    int* ans = new int[values.size()+1];
    for (unsigned int i=0; i<values.size(); i++)
        ans[i]=values[i];
    ans[values.size()]=-1;
    return ans;
}
