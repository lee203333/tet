#pragma once
#include<Windows.h>
#include<array>
#include<map>
using namespace std;

#include<GdiPlus.h>
#pragma comment(lib,"gdiplus")
using namespace Gdiplus;

#ifndef B_SIZE 10
#define B_SIZE 10
#endif

#ifndef B_X_NUM
#define B_X_NUM 20
#endif

#ifndef B_Y_NUM
#define B_Y_NUM 30
#endif

#ifndef INIT_POS_X
#define INIT_POS_X 90
#endif


enum RotateCount
{
	None,
	Once,
	Twice,
	Thrice
};
class MinoShape
{
protected:
	int width, height;

	Point new_Pos;
	void _rotate(int x, int y);
	RotateCount count;
public:
	MinoShape();
	virtual ~MinoShape();
	virtual array<Rect,4>& Rotate(array<Rect,4> &rects,int PosX, int PosY);
	int GetWidth();
	int GetHeight();
	void up_RotateCount();
};

class iShape: MinoShape
{
	iShape(array<Rect,4> &rects);
public:
	~iShape();
	array<Rect,4>& Rotate(array<Rect,4> &rects,int PosX, int PosY);
	friend class iShapeFactory;
};

class oShape: MinoShape
{
	oShape(array<Rect,4> &rects);
public:
	~oShape();
	array<Rect,4>& Rotate(array<Rect,4> &rects,int PosX, int PosY);
	friend class oShapeFactory;
};

class sShape: MinoShape
{
	sShape(array<Rect,4> &rects);
public:
	~sShape();
	array<Rect,4>& Rotate(array<Rect,4> &rects,int PosX, int PosY);
	friend class sShapeFactory;
};

class tShape: MinoShape
{
	tShape(array<Rect,4> &rects);
public:
	~tShape();
	array<Rect,4>& Rotate(array<Rect,4> &rects,int PosX, int PosY);
	friend class tShapeFactory;
};

class lShape: MinoShape
{
	lShape(array<Rect,4> &rects);
public:
	~lShape();
	array<Rect,4>& Rotate(array<Rect,4> &rects,int PosX, int PosY);
	friend class lShapeFactory;
};

//////////////////////////////////////////////////////////
class IMinoShapeFactory
{
public:
	IMinoShapeFactory();
	virtual ~IMinoShapeFactory();
	virtual MinoShape* make(array<Rect,4> &rects) const=0;
};

class iShapeFactory :IMinoShapeFactory
{
public:
	iShapeFactory();
	~iShapeFactory();
	MinoShape* make(array<Rect,4> &rects) const;
};

class oShapeFactory :IMinoShapeFactory
{
public:
	oShapeFactory();
	~oShapeFactory();
	MinoShape* make(array<Rect,4> &rects) const;
};

class sShapeFactory :IMinoShapeFactory
{
public:
	sShapeFactory();
	~sShapeFactory();
	MinoShape* make(array<Rect,4> &rects) const;
};

class tShapeFactory :IMinoShapeFactory
{
public:
	tShapeFactory();
	~tShapeFactory();
	MinoShape* make(array<Rect,4> &rects) const;
};

class lShapeFactory :IMinoShapeFactory
{
public:
	lShapeFactory();
	~lShapeFactory();
	MinoShape* make(array<Rect,4> &rects) const;
};

class MinoShapeFactory
{
	map<int, IMinoShapeFactory* > shape_factories;
public:
	MinoShapeFactory();
	MinoShape* make_shape(array<Rect,4> &rects, int num);
	~MinoShapeFactory();
};
