#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <queue>

using namespace std;

int a[4][4]={};
int fir[4][4]={};

void onClick(char t);

int numb()
{
	int t=0;
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			if (a[i][j]!=0)
				t++;
	return t;
}

void add(int x)
{
	int i, j;
	bool b=false;
	for (int k=0; k<4; k++)
		for (int d=0; d<4; d++)
		{
			if (fir[k][d]!=a[k][d])
			{
				b=true;
				d=4;
				k=4;
			}
		}
	if (b || x==0)
	{
	if (numb()==16)
	{
		cout << "Вы праігралі!" << endl;
		exit(0);
	}
	else
	{
		do
		{
			i=rand()%4, j=rand()%4;
		}
		while (a[i][j]!=0);
		int type=rand()%5;
		type<=3 ? a[i][j]=2 : a[i][j]=4;	
	}
	for (int k=0; k<4; k++)
		for (int d=0; d<4; d++)
			fir[k][d]=a[k][d];
	}
}

void show()
{
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
			cout << setw(3) << a[i][j] << " ";
		cout << endl;
	}
}

int main()
{
	srand(time(NULL));
	char t;
	add(0);
	add(0);
	while (true)
	{
		show();
		cin >> t;
		cout << endl;
		onClick(t);
	}
	return 0;
}

void onClick(char t)
{
	queue <int> q;
	if (t=='s' || t=='S')
	{
		for (int i=0; i<4; i++)
		{
			for (int j=3; j>=0; j--)
			{
				if (a[j][i]!=0) 
				{
					q.push(a[j][i]);
					a[j][i]=0;
				}
			}
			int pos=3;
			bool d=true;
			while (!q.empty())
			{
				if (pos<3 && d && a[pos+1][i]==q.front())
				{
					d=false;
					a[pos+1][i]*=2;
				}
				else
				{
					a[pos][i]=q.front();
					pos--;
					d=true;
				}
				q.pop();
			}
		}
	}
	else if (t=='w' || t=='W')
	{
		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				if (a[j][i]!=0) 
				{
					q.push(a[j][i]);
					a[j][i]=0;
				}
			}
			int pos=0;
			bool d=true;
			while (!q.empty())
			{
				if (pos>0 && d && a[pos-1][i]==q.front())
				{
					d=false;
					a[pos-1][i]*=2;
				}
				else
				{
					a[pos][i]=q.front();
					pos++;
					d=true;
				}
				q.pop();
			}
		}
	}
	else if (t=='d' || t=='D')
	{
		for (int i=0; i<4; i++)
		{
			for (int j=3; j>=0; j--)
			{
				if (a[i][j]!=0) 
				{
					q.push(a[i][j]);
					a[i][j]=0;
				}
			}
			int pos=3;
			bool d=true;
			while (!q.empty())
			{
				if (pos<3 && d && a[i][pos+1]==q.front())
				{
					d=false;
					a[i][pos+1]*=2;
				}
				else
				{
					a[i][pos]=q.front();
					pos--;
					d=true;
				}
				q.pop();
			}
		}
	}
	else if (t=='A' || t=='a')
	{
		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				if (a[i][j]!=0) 
				{
					q.push(a[i][j]);
					a[i][j]=0;
				}
			}
			int pos=0;
			bool d=true;
			while (!q.empty())
			{
				if (pos>0 && d && a[i][pos-1]==q.front())
				{
					d=false;
					a[i][pos-1]*=2;
				}
				else
				{
					a[i][pos]=q.front();
					pos++;
					d=true;
				}
				q.pop();
			}
		}
	}
	add(1);
}
