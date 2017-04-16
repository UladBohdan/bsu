//2. Написать функцию, которая  находит минимальный элемент массива. 
//С использованием этой функции реализовать сортировку числового массива.

#include <iostream>

using namespace std;

int mn_elem(int a[], int n)
{
	int mn=0;
	for (int i=1; i<n; i++)
		if (a[i]<a[mn])
			mn=i;
	return mn;
}

int main()
{
	int n, a[100];
	cout << "Uviadzice kolkasc elementau (<=100)" << endl;
	cin >> n;
	cout << "Uviadzice elementy:" << endl;
	for (int i=0; i<n; i++)
		cin >> a[i];
	for (int i=0; i<n-1; i++)
		swap(a[i],a[i+mn_elem(a+i,n-i)]);
	for (int i=0; i<n; i++)
		cout << a[i] << " ";
	return 0;
}
