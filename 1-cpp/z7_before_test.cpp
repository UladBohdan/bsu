#include <iostream>
#include <algorithm>

using namespace std;

int work_with (string s)
{
	if (s[0]=='-' || (s[0]>=48 && s[0]<=57)) // When it's a number
	{
		int ans=0;
		unsigned int start;
		s[0]=='-' ? start=1 : start=0;
		for (unsigned int i=start; i<s.length(); i++)
			ans=ans*10+s[i]-48;
		if (start==1)
			ans*=-1;
		return ans;
	}
	string oper, a, b;
	oper=s.substr(0,3);
	int st=0;
	if (oper!="neg" && oper!="abs")
	{
		for (unsigned int i=4; i<s.length()-1; i++)
		{
			if (s[i]=='(')
				st++;
			else if (s[i]==')')
				st--;
			if (s[i]==',' && st==0)
			{
				a=s.substr(4,i-4);
				b=s.substr(i+1, s.length()-i-2);
				i=s.length();
			}
		}	
		if (oper=="max") return max(work_with(a),work_with(b));
		else if (oper=="min") return min(work_with(a),work_with(b));
		else if (oper=="add") return work_with(a)+work_with(b);
		else if (oper=="sub") return work_with(a)-work_with(b);
	}
	else
	{
		a=s.substr(4,s.length()-5);
		if (oper=="neg") return -1*work_with(a);
		else if (oper=="abs") return abs(work_with(a));
	}
	return 0;
}

int main()
{
	string s;
	cout << "Enter your expression (you can use functions add, sub, neg, abs, max, min): " << endl;
	cout << "For example: add(max(56,67),abs(-67))" << endl;
	cin >> s;
	cout << work_with(s);
	return 0;
}
