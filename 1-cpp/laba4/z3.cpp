//3. Написать функцию, которая производит двоичный поиск места размещения нового элемента в упорядоченном массиве. 
//С помощью данной функции реализовать сортировку (вставками).

#include <iostream>

using namespace std;

int where (int a[], int n, int val) // binarny posuk
{
	int l=0, r=n-1;
	if (l==r)
	{
		if (val>a[0])
			return 1;
		else
			return 0;
	}
	while (l<r)
	{
		if (r==l+1)
		{	
			if (val>a[r])
				return r+1;
			else if (val<a[l])
				return l;
			else
				return r;
		}
		int t=(l+r)/2;
		if (a[t]>val)
			r=t;
		else if (a[t]<val)
			l=t;
		else
			return t;
	}
	return l;
}

int main()
{
	int n, a[100], b[100]={}, k=1;
	cout << "Uviadzicie kolkasc elementau (<=100)" << endl;
	cin >> n;
	cout << "Uviadzicie elementy:" << endl;
	for (int i=0; i<n; i++)
		cin >> a[i]; 
	b[0]=a[0];
	for (int i=1; i<n; i++)
	{
		int new_place=where(b,k,a[i]);
		for (int j=k; j>new_place; j--)
			b[j]=b[j-1];
		b[new_place]=a[i];	
		k++;
	}
	for (int i=0; i<n; i++)
		cout << b[i] << " ";
	return 0;
}
