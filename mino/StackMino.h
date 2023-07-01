#pragma once
#include<wchar.h>
#include<array>
using namespace std;

#include"MinoColor.h"//gdi
//#include"Observer.hpp"

#ifndef B_SIZE 
#define B_SIZE 10
#endif

#ifndef B_X_NUM 
#define B_X_NUM 20
#endif

#ifndef  B_Y_NUM 30
#define B_Y_NUM 30
#endif

#ifndef INIT_POS_X
#define INIT_POS_X 90
#endif


class StackMino
{
	array<int,B_Y_NUM> stack[B_X_NUM];
	ColorAdapter adapt;
	Color C;

public:
	StackMino();
	~StackMino() {}
	
	//그리기 관련
	int jLength(int i);
	Color& GetColor(int i, int j);
	int GetPosX(int i);
	int GetPosY(int j);

	friend class StackModifier;
	friend class StackBingoProcess;
};

class Modifier
{
protected:
	Modifier* next;
public:
	explicit Modifier() {		next=nullptr;	}

	void add(Modifier *modifier)
	{
		if(next)   next->add(modifier);
		else next = modifier;
	}
	void SetnextNull(){		next=nullptr;	}
	virtual void handle(StackMino& source,array<int,4> &bingoLine)
	{
		if(next) next->handle(source,bingoLine);
	}
};


class StackModifier 
{
	StackMino& stackMino;
	Modifier modifier;

	int BingoLine();
	bool CheckMino(array<Rect,4> &rects, MinoColor mColor);
	void InsertMino(array<Rect,4> &rects, MinoColor mColor);
public:
	StackModifier(StackMino& stack_mino) : stackMino(stack_mino) { }
	~StackModifier() {}

	void add(Modifier *_modifier)
	{
		modifier.add(_modifier);
	}

	friend class SingleMinoCommand;
};

class SingleMino;
class SingleMinoCommand;

class SingleResetProcess : Modifier
{
	SingleMino *single; 
	int *page;

public:
	SingleResetProcess(SingleMino *s, int *page)
		: single(s), page(page) {		next=nullptr;	}
	~SingleResetProcess() {}
	void SetSingleMino(SingleMino *single_mino);

	void handle(StackMino& source,array<int,4> &bingoLine );
};

class StackBingoProcess : Modifier
{
	SingleMino *single; 

	void SetZero(StackMino& source, int num);
	void Pull(StackMino& source, int num);
public:
	StackBingoProcess(SingleMino *s): single(s) {		next=nullptr;	}
	~StackBingoProcess() {}
	void SetSingleMino(SingleMino *single_mino);

	void handle(StackMino& source,array<int,4> &bingoLine );
};

class ScoreProcess : Modifier
{
	int score;
	wchar_t wScore[4];
public:
	ScoreProcess(int s=0): score(s) {		next=nullptr;	}
	~ScoreProcess() {}

	void handle(StackMino& source,array<int,4> &bingoLine );
	int GetScore();
	LPWSTR GetwScore();
};

void update(SingleMino *single, StackMino &stack);

