//2. Продолжить вычисление выражения с учетом приоритета операций. 
//Усложнить за счет введения вложенных скобок. 
//Для решения найдите алгоритм перевода в обратную польскую запись  алгебраического выражения

#include <iostream>
#include <stack>

using namespace std;

string standart_to_polska (string a)
{
	const int M=9998999;
	string ans="";
	a+="+";
	for (unsigned int i=1; i<a.length(); i++) // Change '-' (for negative numbers) on '%'
		if (a[i]=='-' && (a[i-1]<48 || a[i-1]>57) && a[i-1]!=')')
			a[i]='%';
	stack <char> symb;
	int temp=M;
	bool neg=false;
	unsigned int where=0;
	if (a[0]=='-')
	{
		where=1;
		neg=true;
	}
	for (unsigned int i=where; i<a.length(); i++)
	{
		if (a[i]>=48 && a[i]<=57)
		{
			if (temp==M)
				temp=a[i]-48;
			else
				temp=temp*10+a[i]-48;
		}
		else if (a[i]=='%')
		{
			neg=true;
		}
		else
		{
			if (temp!=M)
			{
				if (neg)
					ans+='-';
				stack <int> stemp;
				if (temp==0)
					ans+="0";
				while (temp>0)
				{
					stemp.push(temp%10);
					temp/=10;
				}
				while (!stemp.empty())
				{
					ans+=(stemp.top()+48);
					stemp.pop();
				}
				ans+=" ";
			}
			neg=false;
			temp=M;
			if (a[i]==')')
			{
				while (symb.top()!='(')
				{
					ans+=(symb.top());
					ans+=" ";
					symb.pop();
				}
				symb.pop();
				
			}
			else if (!symb.empty() && (a[i]=='+' || a[i]=='-') && (symb.top()=='*' || symb.top()=='/'))
			{
				while (!symb.empty() && symb.top()!='(')
				{
					ans+=(symb.top());
					ans+=" ";
					symb.pop();
				}
				symb.push(a[i]);
			}
			else
				symb.push(a[i]);
		}
	}
	symb.pop();
	while (!symb.empty())
	{
		ans+=symb.top();
		ans+=" ";
		symb.pop();
	}
	return ans;
}

double count_polska (string a)
{
	stack <double> ans;
	while (a.length()>=1)
	{
		int pl=a.find(' ');
		if (a[0]=='-' && a[1]>=48 && a[1]<=57)
		{
			double temp=0;
			for (int i=1; i<pl; i++)
				temp=temp*10+a[i]-48;
			temp*=-1;
			ans.push(temp);
		}
		else if (a[0]>=48 && a[0]<=57)
		{
			double temp=0;
			for (int i=0; i<pl; i++)
				temp=temp*10+a[i]-48;
			ans.push(temp);
		}
		else
		{
			double num2=ans.top();
			ans.pop();
			double num1=ans.top();
			ans.pop();
			if (a[0]=='+')
				ans.push(num1+num2);
			else if (a[0]=='-')
				ans.push(num1-num2);
			else if (a[0]=='*')
				ans.push(num1*num2);
			else if (a[0]=='/')
				ans.push(num1/num2);
		}
		a=a.substr(pl+1,a.length()-pl);
	}
	return ans.top();
}

int main()
{
	string s;
	cout << "Enter an expression: " << endl;
	cin >> s;
	cout << "Answer: " << count_polska(standart_to_polska(s));
	return 0;
}
