//Fibonacci for logN
//using matrix (1,1,1,0)

#include <iostream>
#include <utility>

using namespace std;

int main()
{
	int n;
	cout << "Input n:" << endl;
	cin >> n;
	n--;
	pair<int,int> a(1,0);
	int m[4]={1,1,1,0}, t[4];
	while (n>0)
	{
		if (n%2==0)
		{
			t[0]=m[0]*m[0]+m[1]*m[2];
			t[1]=m[0]*m[1]+m[1]*m[3];
			t[2]=m[0]*m[2]+m[2]*m[3];
			t[3]=m[1]*m[2]+m[3]*m[3];
			m[0]=t[0];
			m[1]=t[1];
			m[2]=t[2];
			m[3]=t[3];
			n/=2;
		}
		else
		{
			int t=a.first;
			a.first=a.first*m[0]+a.second*m[2];
			a.second=t*m[1]+a.second*m[3];
			n--;
		}
	}
	cout << a.first;
	return 0;
}
