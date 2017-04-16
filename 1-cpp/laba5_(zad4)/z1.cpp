//Функция находит в строке десятичные константы и собирает их в отдельный массив. 

#include <iostream>

using namespace std;

int main()
{
	string a;
	cin >> a;
	int mas[100], n=0;
	long long temp=-1;
	for (unsigned int i=0; i<a.length(); i++)
	{
		if (a[i]>=48 && a[i]<=57)
		{
			if (temp!=-1)
			{
				temp*=10;
				temp+=(a[i]-48);
			}
			else
				temp=a[i]-48;
		}
		else if (temp!=-1)
		{
			mas[n]=temp;
			n++;
			temp=-1;
		}
		if (a.length()-1==i && temp!=-1)
		{
			mas[n]=temp;
			n++;
		}
	}
	if (n==0)
	{
		cout << "No const:(";
		return 0;
	}
	for (int i=0; i<n; i++)
		cout << mas[i] << " ";
	return 0;
}
