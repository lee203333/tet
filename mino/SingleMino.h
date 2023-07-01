#pragma once

#include"MinoShape.h"//including GdiPlus&map
#include"MinoColor.h"

#ifndef INIT_POS_X
#define INIT_POS_X 90
#endif

struct SingleMino
{
private:
	MinoColor color;
	ColorAdapter adapt;
	MinoShape* shape;
	array<Rect,4> rects;
	Point NowPos;
	
	void SetRects(array<Rect,4> &_rects);
	array<Rect,4>& Rotate();
	array<Rect,4>& MoveX(int howMuch);
	array<Rect,4>& MoveY(int howMuch);
public:
	bool show;

	SingleMino();
	~SingleMino();
	void reset();
	
	Color& GetColor();
	Rect* GetRects();
	
	int GetPosX() {		return NowPos.X;	}
	int GetPosY() {		return NowPos.Y;	} 

	friend class SingleMinoCommand;
};
