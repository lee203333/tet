#include<stdlib.h>
#define R(n) (rand()%n)

#include"SingleMino.h"


//ÀÚµ¿
SingleMino::SingleMino()
{
	color = (MinoColor)R(3);
	MinoShapeFactory factory;
	shape = factory.make_shape(rects, R(5)); //alloc
	NowPos = Point(INIT_POS_X,0);
	show = false;
}

void SingleMino::reset()
{
	color = (MinoColor)R(3);
	delete shape;
	MinoShapeFactory factory;
	shape = factory.make_shape(rects, R(5)); //alloc
	NowPos = Point(INIT_POS_X,0);
	show = false;
}

SingleMino::~SingleMino() {			delete shape;		}


Rect* SingleMino::GetRects() {		return (Rect*)&rects;		}
Color& SingleMino::GetColor() 
{
	return adapt.from( color );
}

array<Rect,4>& SingleMino::Rotate()
{	
		return	shape->Rotate(rects,NowPos.X,NowPos.Y);		
}
array<Rect,4>& SingleMino::MoveX(int howMuch)
{
	array<Rect,4> result=rects;
	for(int i=0; i<4; ++i)
	{
		result[i].X= rects[i].X+howMuch;
		if(result[i].X<0 || (result[i].X)>(B_X_NUM-1)*(B_SIZE+1)) return rects;
	}
	return result;
}
array<Rect,4>& SingleMino::MoveY(int howMuch)
{
	array<Rect,4> result=rects;
	for(int i=0; i<4; ++i)
	{
		result[i].Y = rects[i].Y+howMuch;
		if(result[i].Y<0 || (result[i].Y)> (B_Y_NUM-1)*(B_SIZE+1)) return rects;
	}
	return result;
}
void SingleMino::SetRects(array<Rect,4> &_rects)
{
	int minX=B_X_NUM*(B_SIZE+1);
	int minY=(B_Y_NUM-1)*(B_SIZE+1);
	for(int i=0; i<4; ++i)
	{
		rects[i].X=_rects[i].X;
		rects[i].Y=_rects[i].Y;
		rects[i].Width=_rects[i].Width;
		rects[i].Height=_rects[i].Height;
		if(minX > rects[i].X) minX=rects[i].X;
		if(minY > rects[i].Y) minY=rects[i].Y;
	}
	NowPos.X=minX;
	NowPos.Y=minY;
}
