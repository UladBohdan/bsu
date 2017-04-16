//1. Создать односвязный список целых чисел. 
//Сортировать список путем поиска элемента с минимальным значением в оставшейся части списки 
//и перестановки его с первым элементом в этой оставшейся части списка.

#include <iostream>
#include "singly_linked_list.h"

using namespace std;

class singly_linked_list; //Class with method "sort"

int main()
{
	int n, a;
	singly_linked_list ab;
	cout << "Enter N: ";
	cin >> n;
	cout << "Enter your N numbers: ";
	for (int i=0; i<n; i++)
	{
		cin >> a;
		ab.push_front(a);
	}
	ab.sort();
	cout << "Sorted: ";
	ab.show();
	return 0;
}
