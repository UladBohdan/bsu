//1. Реализовать функцию сортировки числового массива по возрастанию (например «пузырьком»).

#include <iostream>

using namespace std;

void sort(int a[], int n)
{
	for (int i=0; i<n-1; i++)
		for (int j=i+1; j<n; j++)
			if (a[j]<a[i]) swap(a[j],a[i]);
}

int main()
{
	int n, a[100];
	cout << "Uviadzice kolkasc elementau (<=100)" << endl;
	cin >> n;
	cout << "Uviadzice elementy:" << endl;
	for (int i=0; i<n; i++)
		cin >> a[i];
	sort(a,n);
	for (int i=0; i<n; i++)
		cout << a[i] << " ";
	return 0;
}
