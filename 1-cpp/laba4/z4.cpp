//Двумерная матрица задает высоты соседствующих клеток местности. 
//Переход возможен в соседние клетки по горизонтали или по вертикали, если высота соседа меньше (как стекает вода).
// ...

#include <iostream>
#include <queue>
#include <stdlib.h>
#include <iomanip>
#include <time.h>

using namespace std;

int a[100][100];

struct p
{
	int x, y, from;
};

void gen(int n, int m)
{
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			int mn=min(min(i,j),min(n-i,m-j));
			a[i][j]=mn*(mn+1)+rand()%25;
			cout << setw(3) << a[i][j] << " ";
		}
	cout << endl;
	}
}

int main()
{
	srand(time(NULL));	
	string str;
	int n, m, x, y, b[100][100]={}, way[100][100]={};
	int mx_b=0, mx_x=0, mx_y=0;
	cout << "Input number of rows, cols (size of matrix, <100): ";
	cin >> n >> m;
	cout << "Generate the matrix? y/n" << endl;
	cin >> str;
	if (str=="y")
		gen(n,m);
	else
	{
		cout << "Input your matrix: " << endl;
		for (int i=0; i<n; i++)
		{
			for (int j=0; j<m; j++)
				cin >> a[i][j];
		}
	}
	cout << "Enter the place to start (row,col): ";
	cin >> x >> y;
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
			way[i][j]=-2;
	queue < p > q;
	p temp;
	x--;
	y--;
	temp.x=x;
	temp.y=y;
	temp.from=-1;
	q.push(temp);
	while (!q.empty())
	{
		int pos_x=q.front().x, pos_y=q.front().y, from=q.front().from;
		q.pop();
		way[pos_x][pos_y]=from;
		if (from==-1)
			b[pos_x][pos_y]=1;
		else if (from==1)
			b[pos_x][pos_y]=b[pos_x][pos_y+1]+1;
		else if (from==0)
			b[pos_x][pos_y]=b[pos_x-1][pos_y]+1;
		else if (from==3)
			b[pos_x][pos_y]=b[pos_x][pos_y-1]+1;
		else if (from==2)
			b[pos_x][pos_y]=b[pos_x+1][pos_y]+1;
		//Looking for the farthest
		if (b[pos_x][pos_y]>mx_b)
		{
			mx_b=b[pos_x][pos_y];
			mx_x=pos_x;
			mx_y=pos_y;
		}
		if (pos_x+1<n && b[pos_x+1][pos_y]==0 && a[pos_x+1][pos_y]<a[pos_x][pos_y])
		{			
			temp.x=pos_x+1;
			temp.y=pos_y;
			temp.from=0;
			q.push(temp);
		}
		if (pos_x-1>=0 && b[pos_x-1][pos_y]==0 && a[pos_x-1][pos_y]<a[pos_x][pos_y])
		{
			temp.x=pos_x-1;
			temp.y=pos_y;
			temp.from=2;
			q.push(temp);
		}
		if (pos_y+1<m && b[pos_x][pos_y+1]==0 && a[pos_x][pos_y+1]<a[pos_x][pos_y])
		{
			temp.x=pos_x;
			temp.y=pos_y+1;
			temp.from=3;
			q.push(temp);
		}
		if (pos_y-1>=0 && b[pos_x][pos_y-1]==0 && a[pos_x][pos_y-1]<a[pos_x][pos_y])
		{			
			temp.x=pos_x;
			temp.y=pos_y-1;
			temp.from=1;
			q.push(temp);
		}
	}
	//Output:
	cout << endl;
	cout << "ANSWER:" << endl;
	cout << endl;
	cout << "Cells we can get into: (1 - we can, 0 - we can`t)" << endl;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
			!b[i][j] ? cout << "0 " : cout << "1 ";
		cout << endl;
	}
	cout << "The farthest cell we can get in: row=" << mx_x+1 << " and col=" << mx_y+1 << endl;
	cout << "How to get to the farthest from the start: " << endl;
	int temp_x=mx_x, temp_y=mx_y;
	while (way[temp_x][temp_y]!=-1)
	{
		int from=way[temp_x][temp_y];
		way[temp_x][temp_y]=-1;
		if (from==0)
			temp_x--;
		else if (from==1)
			temp_y++;
		else if (from==2)
			temp_x++;
		else if (from==3)
			temp_y--;
	}
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<m; j++)
		{
			if (i==x && j==y)
				cout << "S ";
			else if (i==mx_x && j==mx_y)
				cout << "F ";
			else
				way[i][j]==-1 ? cout << "@ " : cout << "- ";
		}
		cout << endl;
	}
	return 0;
}
