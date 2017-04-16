#include <iostream>
#include <cmath>

using namespace std;

// 7 65432 5332222
// 5 432 3222

int main()
{
	int n, dig[10]={};
	string a;
	cin >> n >> a;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<=a[i]-48; j++)
			dig[j]++;
	}
	dig[2]+=(3*dig[8]+dig[6]+2*dig[4]);
	dig[3]+=(2*dig[9]+dig[6]);
	for (int i=0; i<dig[7]; i++)
	{
		cout << 7;
		dig[5]--;
		dig[3]-=2;
		dig[2]-=4;
	}
	for (int i=0; i<dig[5]; i++)
	{
		cout << 5;
		dig[3]--;
		dig[2]-=3;
	}
	for (int i=0; i<dig[3]; i++)
	{
		cout << 3;
		dig[2]--;
	}
	for (int i=0; i<dig[2]; i++)
		cout << 2;
	return 0;
}
