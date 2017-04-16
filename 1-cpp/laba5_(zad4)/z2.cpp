//Функция заменяет их на шестнадцатеричные с тем же значением, например, «ааааа258ххх» на «ааааа0х102ххх».

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	string a;
	cin >> a;
	long long temp=-1;
	for (unsigned int i=0; i<a.length(); i++)
	{
		if (a[i]<48 || a[i]>57)
		{
			cout << a[i];
			if (temp!=-1)
				cout << "0x" << hex << temp;
			temp=-1;
		}
		else
		{
			if (temp==-1)
				temp=a[i]-48;
			else
				temp=temp*10+a[i]-48;
		}
		if (i==a.length()-1 && temp!=-1)
			cout << "0x" << hex << temp;
	}
	return 0;
}
