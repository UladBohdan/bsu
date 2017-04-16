#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int k;
	cout << "Uviadzicie k: ";
	cin >> k;
	cout << k << "aja licba: ";
	int temp=1;
	while (k-(int)(log10(temp))-1>0)
	{
		k-=((int)log10(temp)+1);
		temp++;
	}
	while ((int)log10(temp)+1!=k)
		temp/=10;
	cout << temp%10;
	return 0;
}
