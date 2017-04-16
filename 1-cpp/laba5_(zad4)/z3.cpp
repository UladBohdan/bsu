//Разделители чисел в строке – знаки операций + и -. Вычислить значение выражения.

#include <iostream>

using namespace std;

int main()
{
	string a;
	cin >> a;
	a+='+';
	long long temp=0, ans=0;
	char zn='+';
	for (unsigned int i=0; i<a.length(); i++)
	{
		if (a[i]!='-' && a[i]!='+')
		{
			temp=temp*10+a[i]-48;
		}
		else
		{
			if (zn=='+')
				ans+=temp;
			else
				ans-=temp;
			temp=0;
			zn=a[i];
		}
	}
	cout << ans;
	return 0;
}
