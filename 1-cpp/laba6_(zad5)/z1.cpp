//1. Напишите программу, которая определит, правильно ли расставлены скобки в выражении, 
//если оно состоит из скобок типа: ( ) [ ] { }. (использовать структуру данных стек). 
//Стек отобразить: а)на массив; б)на списковую структуру

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	char x;
	string t;
	int pos=1, a[100]={};
	cin >> t;
	for (unsigned int i=0; i<t.length(); i++)
	{
		x=t[i];
		int temp;
		if (x=='{')
			temp=1;
		else if (x=='}')
			temp=-1;
		else if (x=='(')
			temp=2;
		else if (x==')')
			temp=-2;
		else if (x=='[')
			temp=3;
		else if (x==']')
			temp=-3;
		if (temp<0 && temp==-1*a[pos-1])
			pos--;
		else
		{
			a[pos]=temp;
			pos++;
		}
	}
	if (pos!=1)
		cout << "Wrong expression";
	else
		cout << "Right expression";
	return 0;
}
