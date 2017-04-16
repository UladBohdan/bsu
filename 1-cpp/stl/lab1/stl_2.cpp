#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
	ifstream fin("input");
	string rd;
	list <string> lst;
	while (!fin.eof())
	{
		fin >> rd;
		lst.push_back(rd);
	}
	cout << "our words: ";
	for (list<string>::iterator i = lst.begin(); i!=lst.end(); i++)
		cout << *i << " ";
	cout << endl << "sorted list: ";
	lst.sort();
	for (list<string>::iterator i = lst.begin(); i!=lst.end(); i++)
		cout << *i << " ";
	cout << endl << "words on W: ";
	list<string>::iterator b, e;
	bool found=false;
	for (list<string>::iterator i = lst.begin(); i!=lst.end(); i++)
	{
		if ((*i)[0]=='w')
			cout << *i << " ";
		if ((*i)[0]=='t' && found==false)
		{
			b=i;
			found=true;
		}
		if ((*i)[0]!='t' && found==true)
		{
			e=i;
			found=false;
		}
	}
	lst.erase(b,e);
	cout << endl << "deleting words on T..." << endl << "new list: ";
	for (list<string>::iterator i = lst.begin(); i!=lst.end(); i++)
		cout << *i << " ";
	return 0;
}
