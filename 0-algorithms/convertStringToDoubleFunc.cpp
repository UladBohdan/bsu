#include <iostream>

using namespace std;

// This function converts strings like "-123.45E+2" into a double
// Shen 5.2.1 - 5.2.5

double convertStringToDouble(string s, bool& ok)
{
    #define FINISH_CASE else if (s[pos]=='$') state=FINAL; else state=ERROR; break;
    enum states { INIT, SIGNBEG, INTDIGIT, POINT, DECDIGIT, E_EXISTS, E_DIGIT, FINAL, ERROR };

    double ans=0. , toDivide=1. ;
    int pos=0, sign=1, esign=1, e=0;
    states state=INIT;
    ok=true;

    s+="$";     // string end
    while (state!=FINAL && state!=ERROR)
    {
        switch (state)
        {
        case INIT:
            if (s[pos]=='+' || s[pos]=='-')
                state=SIGNBEG;
            else if (s[pos]>=48 && s[pos]<=57)
                state=INTDIGIT;
            else if (s[pos]=='.')
                state=POINT;
            FINISH_CASE

        case SIGNBEG:
            if (s[pos]=='-')
                sign=-1;
            pos++;
            if (s[pos]>=48 && s[pos]<=57)
                state=INTDIGIT;
            FINISH_CASE

        case INTDIGIT:
            ans=ans*10+(s[pos]-48);
            pos++;
            if (s[pos]>=48 && s[pos]<=57)
                state=INTDIGIT;
            else if (s[pos]=='.')
                state=POINT;
            else if (s[pos]=='E')
                state=E_EXISTS;
            FINISH_CASE

        case POINT:
            pos++;
            if (s[pos]>=48 && s[pos]<=57)
                state=DECDIGIT;
            else if (s[pos]=='E')
                state=E_EXISTS;
            FINISH_CASE

        case DECDIGIT:
            ans=ans*10+(s[pos]-48);
            toDivide/=10.;
            pos++;
            if (s[pos]>=48 && s[pos]<=57)
                state=DECDIGIT;
            else if (s[pos]=='E')
                state=E_EXISTS;
            FINISH_CASE

        case E_EXISTS:
            pos++;
            if (s[pos]=='-')
                esign=-1;
            pos++;
            state=E_DIGIT;
            break;

        case E_DIGIT:
            e=e*10+(s[pos]-48);
            pos++;
            if (s[pos]>=48 && s[pos]<=57)
                state=E_DIGIT;
            else if (s[pos]=='$')
            {
                if (esign==1)
                {
                    while (e>0)
                    {
                        toDivide*=10;
                        e--;
                    }
                }
                else
                {
                    e*=-1;
                    while (e<0)
                    {
                        toDivide/=10.;
                        e++;
                    }
                }
                state=FINAL;
            }
            else
                state=ERROR;
            break;

        case FINAL:
            break;

        case ERROR:
            break;
        }
    }
    ans*=toDivide;
    ans*=sign;

    if (state==ERROR)
    {
        ok=false;
        return 0;
    }
    else
        return ans;
}

int main()
{
    string s="-3.45E-1";
    bool okey;
    double ans=convertStringToDouble(s,okey);
    if (okey)
        cout << ans << endl;
    else
        cout << "Error occured." << endl;
    return 0;
}
