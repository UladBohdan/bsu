#include <iostream>
#include <fstream>
#include "bits.h"

using namespace std;

ifstream fin("input");
ofstream fout("output");

class bits;

bits* intersection(bits* a, bits* b)
{
	bits* temp = new bits;
	for (int i=0; i<256; i++)
		if ((a->find(i)==true) && (b->find(i)==true))
			temp->push(i);
	return temp;
}

void set_out(string text, bits* a)
{
	cout << text;
	fout << text;
	int *from;
	from=a->out();
	int j=0;
	if (from[0]==-1)
	{
		cout << "empty:(" << endl;
		fout << "empty:(" << endl;
		return;
	}
	while (from[j]!=-1)
	{
		cout << from[j] << " ";
		fout << from[j] << " ";
		j++;
	}
	cout << endl;
	fout << endl;
}

int main()
{
	bits* a = new bits;
	bits* b = new bits;
	int n, t;
	fin >> n;
	for (int i=0; i<n; i++)
	{
		fin >> t;
		a->push(t);
	}
	fin >> n;
	for (int i=0; i<n; i++)
	{
		fin >> t;
		b->push(t);
	}
	set_out("1st set: ", a);
	set_out("2nd set: ", b);
	set_out("Their intersection: ", intersection(a,b));
	return 0;
}
