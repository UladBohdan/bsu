//2. В циклическом списке N элементов. Проходим по списку и удаляем каждый к-ый элемент. 
//Повторяем действия для оставшегося списка, пока в нем не останется к-1 элемент. Распечатать окончательный список.

#include <iostream>
#include "cyclic_singly_linked_list.h"

using namespace std;

class cyclic_singly_linked_list;

int main()
{
	cyclic_singly_linked_list ab;
	int n, a, k;
	cout << "Enter N, K: ";
	cin >> n >> k;
	cout << "Enter your N numbers: ";
	for (int i=0; i<n; i++)
	{
		cin >> a;
		ab.push_back(a);
	}
	cout << "Your list: ";
	ab.show();
	ab.make_less(k-1);
	cout << "Your K-1 elements: ";
	ab.show(); 
	return 0;
}
