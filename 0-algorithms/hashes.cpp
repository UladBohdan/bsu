#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <list>
#include <utility>
#include <deque>
#include <queue>
#include <stack>

// Hash functions and STL

using namespace std;

unsigned int HashRot13(const char* s)
{
    unsigned int hash=0;
    for (unsigned int i=0; i<strlen(s); i++)
    {
        hash+=(unsigned int)(s[i]);
        hash-=(hash<<13)|(hash>>19);
    }
    return hash;
}

unsigned int HashLy(const char* s)
{
    unsigned int hash = 0;
    for (; *s; s++)
        hash = (hash*1664525) + (unsigned int)(*s) + 1013904223;
    return hash;
}

unsigned int HashRs(const char * s)
{
    static const unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    for(; *s; s++)
    {
        hash = hash * a + (unsigned char)(*s);
        a *= b;
    }
    return hash;
}

unsigned int HashFAQ6(const char * s)
{
    unsigned int hash = 0;
    for (; *s; s++)
    {
        hash += (unsigned char)(*s);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

bool comp(int n)
{
    return (n>=15);
}

int main()
{
   /* map <unsigned int, char*> m;
    srand(time(NULL));
    for (int i=0; i<20; i++)
    {
        int sz=rand()%25+20;
        char* s = new char[sz];
        for (int j=0; j<sz; j++)
            s[j]=rand()%50+32;
        m[HashFAQ6(s)]=s;
    }
    for (map<unsigned int, char*>::iterator i=m.begin(); i!=m.end(); i++)
        cout << setw(10) << i->first << " " << i->second << endl; */

    srand(time(NULL));

    priority_queue<int> q;
    for (int i=0; i<10; i++)
        q.push(rand()%20);
    while (!q.empty())
    {
        cout << q.top() << endl;
        q.pop();
    }
    return 0;
}

