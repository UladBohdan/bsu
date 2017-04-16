#include <iostream>

using namespace std;

// All the sequences of 0,1,2 (length N) without two same neighbouring digits
// SHEN     3.2.2

const int n=3;
int len=1;
string s="0";

void up_up()
{
    while (len!=n)
    {
        if (s[len-1]=='0')
            s+="1";
        else
            s+="0";
        len++;
    }
    cout << s << endl;
    return;
}

bool exists_right()
{
    if (len=='1' && s[len-1]=='2')
        return false;
    else if (s[len-1]=='2')
        return false;
    else if (s[len-1]=='1' && s[len-2]=='2')
        return false;
    return true;
}

void go_right()
{
    if (len==1 || s[len-1]=='1')
        s[len-1]++;
    else
    {
        if (s[len-2]=='1')
            s[len-1]='2';
        else
            s[len-1]='1';
    }
    return;
}

void go_down()
{
    s.erase(s.end()-1,s.end());
    len--;
    return;
}

int main()
{
    up_up();
    while (len!=0)
    {
        if (exists_right())
        {
            go_right();
            up_up();
        }
        else
            go_down();
    }
    return 0;
}
