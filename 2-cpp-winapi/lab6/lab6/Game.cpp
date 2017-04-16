#include "Game.h"

Game::Game() { }

void Game::init(HWND h)
{
	hwnd=h;
}

void Game::start(bool c, bool h, int cl)
{
	comp=c;
	
	cout << endl;
	hard=h;
	color=cl;
	isfin=false;
	boxnotseen=true;
	turn=1;
	for (int i=0; i<9; i++)
	{
		cond[i]=0;
		showwin[i]=false;
	}
	empty=9;
	win=0;
	init(hwnd);
	draw();
cout << "start" << endl;
	for (int i=0; i<9; i++)
		cout << cond[i] << " ";
	if (comp) yourturn();
}

void Game::updateWindowSize(int a, int b)
{
	w=a;
	h=b-20;
	draw();
}

void Game::draw()
{
	HDC hDC=GetDC(hwnd);
	string downtext="You're playing with ";
	if (comp)
		downtext+=(hard ? "computer (hard)." : "computer (random)");
	else
		downtext+=" your friend (RButton)";
	TextOut(hDC,10,h,downtext.c_str(),downtext.length());
	HPEN pen;
	int pos=0, fr=1, frr=7;
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
		{
			Rectangle(hDC,j*w/3+fr,i*h/3+fr,(j+1)*w/3-fr,(i+1)*h/3-fr);
			pen=CreatePen(0,3,RGB(255,0,0));
			SelectObject(hDC,pen);
			if (showwin[pos])
				Rectangle(hDC,j*w/3+fr+3,i*h/3+fr+3,(j+1)*w/3-fr-3,(i+1)*h/3-fr-3);
			pen=CreatePen(0,1,color);
			SelectObject(hDC,pen);
			if (cond[pos]==1)
			{
				MoveToEx(hDC,j*w/3+frr,i*h/3+frr,NULL);
				LineTo(hDC,(j+1)*w/3-frr,(i+1)*h/3-frr);
				MoveToEx(hDC,j*w/3+frr,(i+1)*h/3-frr,NULL);
				LineTo(hDC,(j+1)*w/3-frr,i*h/3+frr);
			}
			else if (cond[pos]==2)
			{
				Ellipse(hDC,j*w/3+frr,i*h/3+frr,(j+1)*w/3-frr,(i+1)*h/3-frr);
			}
			pos++;
		}
	DeleteObject(pen);
	ReleaseDC(hwnd,hDC);
}

void Game::yourturn()
{
	
	cout << endl;
	if (isfin) return;
	Sleep(500);
	if (hard)
	{

	}
	else
	{
		srand(time(NULL));
		int choise=rand()%empty+1;
		for (int i=0; i<9; i++)
		{
			if (!cond[i])
				choise--;
			if (!choise)
			{
				cond[i]=1;
				empty--;
				break;
			}
		}
	}
	cout << "comp" << endl;
	for (int i=0; i<9; i++)
		cout << cond[i] << " ";
	draw();
	isFinished();
}

void Game::onLClick(int x, int y) 
{ 
	if (isfin) return;
	if (comp || turn%2==0)
	{
		int pos=0, curcell=-1;
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
			{
				if (x>j*w/3 && x<(j+1)*w/3 && y>i*h/3 && y<(i+1)*h/3)
				{
					curcell=pos;
					break;
				}
				pos++;
			}
		if (cond[curcell]==0)
		{
			cond[curcell]=2;
			empty--;
			draw();
			isFinished();
			if (comp)
				yourturn();
			else
			{
				turn++;
				draw();
			}
		}
	}
}

void Game::onRClick(int x, int y) 
{ 
	if (isfin) return;
	if (!comp && turn%2==1)
	{
		int pos=0, curcell=-1;
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
			{
				if (x>j*w/3 && x<(j+1)*w/3 && y>i*h/3 && y<(i+1)*h/3)
				{
					curcell=pos;
					break;
				}
				pos++;
			}
		if (cond[curcell]==0)
		{
			cond[curcell]=1;
			turn++;
			empty--;
			draw();
			isFinished();
		}
	}
}

void Game::isFinished()
{
	int a[]={0,1,2, 3,4,5, 6,7,8, 0,3,6, 1,4,7, 2,5,8, 0,4,8, 2,4,6};
	for (int i=0; i<8; i++)
	{
		if (cond[a[3*i]]*cond[a[3*i+1]]*cond[a[3*i+2]]==1)
			win=1;
		if (cond[a[3*i]]*cond[a[3*i+1]]*cond[a[3*i+2]]==8)
			win=2;
		if (win!=0)
		{
			showwin[a[3*i]]=true;
			showwin[a[3*i+1]]=true;
			showwin[a[3*i+2]]=true;
			draw();
			isfin=true;
			finish();
			return;
		}
	}
	if (!empty)
	{
		draw();
		isfin=true;
		finish();
	}
}

void Game::finish()
{ 
	string ans="Game is finished!\n";
	if (win==0)
		ans+="Draw!";
	else if (win==2 && comp)
		ans+="Player won!";
	else if (win==2)
		ans+="Left button player won!";
	else if (win==1 && comp)
		ans+="Computer won!";
	else
		ans+="Rught button player won!";
	ans+="\nResult will be saved to statistics.\n\nStart a new game of the same type?";
	if ((!empty && boxnotseen) || isfin)
	{
		if (MessageBox(hwnd,ans.c_str(),"Game finished!", MB_YESNO) == IDYES)
			start(comp,hard,color);
		else
			boxnotseen=false;
	}
}

Game::~Game() { }