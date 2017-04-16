//to tranfer numbers from one counting system to another
//to do operation with numbers in different counting systems

#include <iostream>
#include <stack>

using namespace std;

class num
{
    int p;
    long long val10;
    public:
        string value;
        num (int osnov, string vall) {value=vall; p=osnov; osn(10);}
        void osn (int n);
        long long operator+ (num b) {return val10+b.val10;};
        long long operator- (num b) {return val10-b.val10;};
        long long operator* (num b) {return val10*b.val10;};
        long long operator/ (num b) {return val10/b.val10;};
};

void num::osn (int n)
{
    //Peravod u 10
    stack <int> s;
    for (int i=value.length()-1; i>=0; i--)
    {
        if (value[i]<=57)
            s.push(value[i]-48);
        else
            s.push(value[i]-55);
    }
    long long ans=s.top();
    s.pop();
    while (!s.empty())
    {
        ans*=p;
        ans+=s.top();
        s.pop();
    }
    p=10;
    val10=ans;
   //Peravod u n
    stack <int> q;
    long long temp=val10;
    while (temp>0)
    {
        q.push(temp%n);
        temp/=n;
    }
    value="";
    while (!q.empty())
    {
        if (q.top()<=9)
            value+=(char)(q.top()+48);
        else
            value+=(char)(q.top()+55);
        q.pop();
    }
}

int main()
{
    int tyop, neew, old;
    string vall, s2;
    char c;
    cout << "Vvedite 1, esli hotite perevesti chislo v druhuy sistemy, 2, esli hotite vypolnit dejstvia" << endl;
    cin >> tyop;
    if (tyop==1)
    {
        cout << "Vvedite vashu sistemu schislenija, vashe chislo i novuju sustemy." << endl << "Naprimer: 10 54 16" << endl;
        cin >> old >> vall >> neew;
        num a(old,vall);
        a.osn(neew);
        cout << a.value;
    }
    else if (tyop==2)
    {
        cout << "Vvedite dva chisla (kazhdoe v formate 16 A5F), mezhdu nimi - odin iz znakov +, -, *, /." << endl << "Tolko nie slishkom bolshije chisla!" << endl;
        cin >> old >> vall >> c;
        num a(old,vall);
        cin >> old >> vall;
        num b(old,vall);
        cout << "Otvet s osnovanijem 10: ";
        if (c=='+') cout << a+b;
        else if (c=='-') cout << a-b;
        else if (c=='*') cout << a*b;
        else if (c=='/') cout << a/b;
    }
    return 0;
}
