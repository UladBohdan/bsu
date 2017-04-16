#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

struct person
{
	string name;
	int year;
	double index;
};

void work_with(string s, person mas[], int num)
{
	int pos=0;
	for (int i=0; i<num; i++)
	{
		mas[i].name="";
		mas[i].index=0;
		while ((s[pos]>=65 && s[pos]<=90) || (s[pos]>=97 && s[pos]<=122))
		{
			mas[i].name+=s[pos];
			pos++;
		}
		mas[i].year=(s[pos]-48)*1000+(s[pos+1]-48)*100+(s[pos+2]-48)*10+s[pos+3]-48;
		pos+=5;
		while (s[pos]>=48 && s[pos]<=57)
		{
			mas[i].index=mas[i].index*10+s[pos]-48;
			pos++;
		}
		if (s[pos]=='.')
		{
			pos++;
			double tmp=0;
			int logtmp=0;
			while (s[pos]>=48 && s[pos]<=57)
			{
				tmp=tmp*10+s[pos]-48;
				logtmp++;
				pos++;
			}
			while (logtmp>0)
			{
				tmp/=10;
				logtmp--;
			}
			mas[i].index+=tmp;
		}
		pos++;
	}
}

void sort(person mas[], int n)
{
	stack <person> s1, s2;
	for (int i=0; i<n-1; i++)
	{
		int mn=i;
		for (int j=i+1; j<n; j++)
			if (mas[j].name<mas[mn].name)
				mn=j;
		swap(mas[mn],mas[i]);
	}
	for (int i=0; i<n; i++)
		s1.push(mas[i]);
	while (!s1.empty())
	{
		s2.push(s1.top());
		s1.pop();
	}
	cout << "Sorted list:" << endl;
	while (!s2.empty())
	{
		cout << "  " << s2.top().name << " " << s2.top().year << " " << s2.top().index << endl;
		s2.pop();
	}
}

void find_average(person mas[], int n)
{
	double av_year=0;
	for (int i=0; i<n; i++)
		av_year+=mas[i].year;
	av_year/=n;
	int mn=fabs(mas[0].year-av_year), mn_pos=0;
	for (int i=1; i<n; i++)
		if (fabs(mas[i].year-av_year)<mn)
		{
			mn_pos=i;
			mn=fabs(mas[i].year-av_year);
		}
	cout << "Person with almost average year: " << mas[mn_pos].name << " (" << mas[mn_pos].year << ", " << mn << " from the average value)" << endl;
}

void index_range(person mas[], int n)
{
	int mx=0, mn=0;
	for (int i=1; i<n; i++)
	{
		if (mas[i].index<mas[mn].index)
			mn=i;
		if (mas[i].index>mas[mx].index)
			mx=i;
	}
	cout << "Index range: " << mas[mn].index << "-" << mas[mx].index << endl;
}

int main()
{
	string s;
	cout << "Enter persons:" << endl;
	getline(cin,s);
	s+=" ";
	int num=0;
	for (unsigned int i=0; i<s.length(); i++)
		if (s[i]==' ')
			num++;
	num/=2;
	person *mas = new person[num];
	work_with(s,mas,num);
	sort(mas,num);
	find_average(mas,num);
	index_range(mas,num);
	return 0;
}
