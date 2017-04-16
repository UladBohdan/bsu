#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <string>
#include <stdlib.h>

using namespace std;

struct flbed
{
	int num;
	string shape;
	vector <string> flw;
};

bool sortshape(flbed a, flbed b)
{
	return (a.shape<b.shape || (a.shape==b.shape && a.num<b.num));
}

bool sortnum(flbed a, flbed b)
{
	return (a.num<b.num);
}

int main()
{
	ifstream fin("flowers");
	string temp;
	vector <flbed> v;
	bool just=false;
	while (!fin.eof())
	{
		fin >> temp;
		if (temp[0]<=57)
		{
			flbed t;
			t.num=v.size();
			v.push_back(t);
			just=true;
		}
		else
		{
			if (just)
				v[v.size()-1].shape=temp;
			else
				v[v.size()-1].flw.push_back(temp);
			just=false;
		}
	}
	v[v.size()-1].flw.pop_back();
	sort(v.begin(),v.end(),sortshape);
	cout << "FLOWERBEDS SORTED BY SHAPE:" << endl;
	for (vector<flbed>::iterator i=v.begin(); i!=v.end(); i++)
	{
		cout << " " << setw(9) << i->shape << " " << setw(1) << i->num+1 << "  ";
		for (vector<string>::iterator j=i->flw.begin(); j!=i->flw.end(); j++)
			cout << *j << " ";
		cout << endl;
	}
	map <string,flbed> m;
	for (vector<flbed>::iterator i=v.begin(); i!=v.end(); i++)
		m[i->shape]=*i;
	cout << endl << "NUMBER OF UNIQUE SHAPES: " << m.size() << endl;
	vector <string> all_flowers;
	for (vector<flbed>::iterator i=v.begin(); i!=v.end(); i++)
	{
		for (vector<string>::iterator j=i->flw.begin(); j!=i->flw.end(); j++)
			all_flowers.push_back(*j);
	}
	sort(all_flowers.begin(), all_flowers.end());
	vector <string> uniq_flowers (all_flowers.size());
	vector<string>::iterator it;
	it=unique_copy(all_flowers.begin(), all_flowers.end(), uniq_flowers.begin());
	uniq_flowers.resize(it-uniq_flowers.begin());
	cout << endl << "ALL KINDS OF FLOWERS:" << endl;
	for (vector<string>::iterator i=uniq_flowers.begin(); i!=uniq_flowers.end(); i++)
		cout << " " << *i << endl;
	srand(time(NULL));
	int r=rand()%v.size();
	cout << endl << "ALL FLOWERS OF RANDOM CHOSEN FLOWERBED - " << r+1 << " :" << endl;
	for (vector<string>::iterator i=v[r].flw.begin(); i!=v[r].flw.end(); i++)
		cout << " " << *i << endl;
	cout << endl << "FLOWERBED WITH MAX NUMBER OF FLOWERS:  number ";
	int* nums = new int[v.size()];
	for (unsigned int i=0; i<v.size(); i++)
		nums[i]=v[i].flw.size();
	cout << v[max_element(nums,nums+v.size())-nums].num+1;
	string randfl=all_flowers[rand()%all_flowers.size()];
	cout << endl << endl << "ALL FLOWERBEDS WITH RANDOM CHOSEN FLOWER " << randfl << ": number ";
	for (vector<flbed>::iterator i=v.begin(); i!=v.end(); i++)
		if (find(i->flw.begin(),i->flw.end(),randfl)!=i->flw.end())
			cout << i->num+1 << " ";
	cout << endl << endl << "FLOWERS WHICH IS IN EACH FLOWERBED: ";
	bool found=false;
	for (unsigned int i=0; i<all_flowers.size(); i++)
	{
		unsigned int t=0;
		for (unsigned int j=0; j<v.size(); j++)
		{
			if (find(v[j].flw.begin(),v[j].flw.end(),all_flowers[i])!=v[j].flw.end())
				t++;
		}
		if (t==v.size())
		{
			found=true;
			cout << all_flowers[i] << " ";
		}
	}
	if (!found) cout << "no such flowers.";
	cout << endl;
	
	vector <string> uniqsmth;
	for (vector<flbed>::iterator i=v.begin(); i!=v.end(); i++)
		uniqsmth.push_back(i->shape);
	cout << endl << "NUMBER OF UNIQUE SHAPES (by standart algorithms): ";
	cout << unique(uniqsmth.begin(),uniqsmth.end())-uniqsmth.begin() << endl;
	
	uniqsmth.clear();
	uniqsmth=vector<string>(all_flowers.begin(),all_flowers.end());
	cout << endl << "NUMBER OF UNIQUE FLOWERS (by standart algorithms): ";
	cout << unique(uniqsmth.begin(),uniqsmth.end())-uniqsmth.begin() << endl;
	
	vector <int> mx;
	for (unsigned int i=0; i<v.size(); i++)
		mx.push_back(v[i].flw.size());
	cout << endl << "FLOWERBED WITH MAX NUMBER OF FLOWERS (by standart algorithm): number ";
	cout << v[max_element(mx.begin(), mx.end())-mx.begin()].num+1 << endl;
	
	sort(v.begin(),v.end(),sortnum);
	r=rand()%v.size();
	randfl=v[r].flw[rand()%v[r].flw.size()];
	cout << endl << "RANDOM SET FLOWER: \"" << randfl << "\" from flowerbed number " << r+1 << "." << endl;
	cout <<"Will be replaced with \"tassel\"" << endl;
	replace(v[r].flw.begin(), v[r].flw.end(), randfl, (string)("tassel"));
	cout << endl << "FINAL LIST OF FLOWERBEDS:" << endl;
	for (vector<flbed>::iterator i=v.begin(); i!=v.end(); i++)	
	{
		cout << " " << i->num+1 << " " << setw(9) << i->shape << "  ";
		for (vector<string>::iterator j=i->flw.begin(); j!=i->flw.end(); j++)
			cout << *j << " ";
		cout << endl; 
	}
	return 0;
}
