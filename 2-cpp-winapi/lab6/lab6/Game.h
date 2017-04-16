#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

using namespace std;

class Game
{
public:
	Game();
	void init(HWND);
	void start(bool,bool,int);
	void onLClick(int,int);
	void onRClick(int,int);
	void yourturn();
	void updateWindowSize(int, int);
	void draw();
	void isFinished();
	void finish();
	~Game();
private:
	int cond[9], w, h, color, empty, turn, win;
	bool comp, hard, boxnotseen, isfin, showwin[9];
	HWND hwnd;
};

