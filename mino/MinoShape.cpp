#define _USE_MATH_DEFINES
#include<math.h>
#define DecFloor(N) floor(((N)*0.1)+0.5)*10
#define Half(N) floor((N)+0.5)
#include"MinoShape.h"


void  MinoShape::_rotate(int PosX, int PosY)
{
	int middle_x = Half(width/2);
	int middle_y = Half(height/2);

	new_Pos.X = PosX+middle_x-middle_y;
	new_Pos.Y = PosY+middle_y-middle_x;
}
void MinoShape::up_RotateCount()
{
	if( count == RotateCount::Thrice )
		count=RotateCount::None;
	else
		count=(RotateCount) (1+(int)count);
}
array<Rect,4>& MinoShape::Rotate(array<Rect,4> &rects,int PosX, int PosY) 
{
	return rects;
}
int MinoShape::GetWidth() {		return width;	}
int MinoShape::GetHeight() {	return height;	}

MinoShape::MinoShape() {}
MinoShape:: ~MinoShape() {}

//.    User Coordinate
// け  
// け   
// け  
// け. 
//    (BottomX, BottomY)
iShape::iShape(array<Rect,4> &rects)
{
	count=RotateCount::None;
	width=B_SIZE;
	height=B_SIZE*4+3;

	for(int i=0; i<4; ++i)
		rects[i]=Rect(INIT_POS_X, (B_SIZE+1)*i ,B_SIZE,B_SIZE);
}
iShape::~iShape() {}
array<Rect,4>& iShape::Rotate(array<Rect,4> &rects,int PosX, int PosY)
{
	_rotate(PosX,PosY);

	if( new_Pos.X<5 || (new_Pos.X+width)>B_X_NUM*(B_SIZE+1)-10 || new_Pos.Y<5 || (new_Pos.Y+height)>(B_Y_NUM)*(B_SIZE+1)-10 )
		return rects;

	up_RotateCount();
	array<Rect,4> result;
	if(count == RotateCount::None || count == RotateCount::Twice)
	{
		for(int i=0; i<4; ++i)
			result[i]=Rect(new_Pos.X, new_Pos.Y+(B_SIZE+1)*i ,B_SIZE,B_SIZE);
	}
	else
	{
		for(int i=0; i<4; ++i)
			result[i]=Rect(new_Pos.X+(B_SIZE+1)*i, new_Pos.Y ,B_SIZE,B_SIZE);
	}
	int temp = width;
	width = height;
	height = temp;

	return result;
}

//.     User Coordinate
// けけ  
// けけ. 
//      (BottomX, BottomY)
oShape::oShape(array<Rect,4> &rects)
{
	count=RotateCount::None;
	width=B_SIZE*2+1;
	height=B_SIZE*2+1;

	rects[0]=Rect(INIT_POS_X,			0		 ,B_SIZE,B_SIZE);
	rects[1]=Rect(INIT_POS_X+B_SIZE+1,	0		 ,B_SIZE,B_SIZE);
	rects[2]=Rect(INIT_POS_X,			B_SIZE+1 ,B_SIZE,B_SIZE);
	rects[3]=Rect(INIT_POS_X+B_SIZE+1,	B_SIZE+1 ,B_SIZE,B_SIZE);
}
array<Rect,4>& oShape::Rotate(array<Rect,4> &rects,int PosX, int PosY) {	return rects;	} //Symmetry
oShape::~oShape() {}


//.   User Coordinate
// け						.      User Coordinate
// けけ						  けけ
//   け.					けけ.
//		(BottomX, BottomY)		  (BottomX, BottomY)
sShape::sShape(array<Rect,4> &rects)
{
	count=RotateCount::None;
	width=B_SIZE*2+1;
	height=B_SIZE*3+2;

	rects[0]=Rect(INIT_POS_X,			0			 ,B_SIZE,B_SIZE);
	rects[1]=Rect(INIT_POS_X,			B_SIZE+1	 ,B_SIZE,B_SIZE);
	rects[2]=Rect(INIT_POS_X+B_SIZE+1,	B_SIZE+1	 ,B_SIZE,B_SIZE);
	rects[3]=Rect(INIT_POS_X+B_SIZE+1,	(B_SIZE+1)*2 ,B_SIZE,B_SIZE);
}
sShape::~sShape() {}
array<Rect,4>& sShape::Rotate(array<Rect,4> &rects,int PosX, int PosY)
{
	_rotate(PosX,PosY);

	if( new_Pos.X<5 || (new_Pos.X+width)>B_X_NUM*(B_SIZE+1)-10 || new_Pos.Y<5 || (new_Pos.Y+height)>(B_Y_NUM)*(B_SIZE+1)-10 )
		return rects;

	up_RotateCount();
	array<Rect,4> result;
	if(count == RotateCount::None || count == RotateCount::Twice)
	{
		result[0]=Rect(new_Pos.X,			 new_Pos.Y			    ,B_SIZE,B_SIZE);
		result[1]=Rect(new_Pos.X,			 new_Pos.Y+(B_SIZE+1)   ,B_SIZE,B_SIZE);
		result[2]=Rect(new_Pos.X+(B_SIZE+1), new_Pos.Y+(B_SIZE+1)   ,B_SIZE,B_SIZE);
		result[3]=Rect(new_Pos.X+(B_SIZE+1), new_Pos.Y+(B_SIZE+1)*2 ,B_SIZE,B_SIZE);
	}
	else
	{
		result[0]=Rect(new_Pos.X+(B_SIZE+1),   new_Pos.Y			,B_SIZE,B_SIZE);
		result[1]=Rect(new_Pos.X+(B_SIZE+1)*2 ,new_Pos.Y			,B_SIZE,B_SIZE);
		result[2]=Rect(new_Pos.X			  ,new_Pos.Y+(B_SIZE+1)	,B_SIZE,B_SIZE);
		result[3]=Rect(new_Pos.X+(B_SIZE+1)   ,new_Pos.Y+(B_SIZE+1) ,B_SIZE,B_SIZE);
	}
	int temp = width;
	width = height;
	height = temp;

	return result;
}

//							.	  User Coordinate				.
//.    User Coordinate		 け						.			   け
//   け						 けけ					 けけけ		 けけ
// けけけ.					 け.					   け		   け
//		  (BottomX, BottomY)	(BottomX, BottomY)
tShape::tShape(array<Rect,4> &rects)
{
	count=RotateCount::None;
	width=B_SIZE*2+1;
	height=B_SIZE*3+2;

	rects[0]=Rect(INIT_POS_X,		0		 ,B_SIZE,B_SIZE);
	rects[1]=Rect(INIT_POS_X,		B_SIZE+1 ,B_SIZE,B_SIZE);
	rects[2]=Rect(INIT_POS_X+B_SIZE+1,	B_SIZE+1 ,B_SIZE,B_SIZE);
	rects[3]=Rect(INIT_POS_X,		(B_SIZE+1)*2 ,B_SIZE,B_SIZE);
}
tShape::~tShape() {}
array<Rect,4>& tShape::Rotate(array<Rect,4> &rects,int PosX, int PosY)
{
	_rotate(PosX,PosY);

	if( new_Pos.X<5 || (new_Pos.X+width)>B_X_NUM*(B_SIZE+1)-10 || new_Pos.Y<5 || (new_Pos.Y+height)>(B_Y_NUM)*(B_SIZE+1)-10 )
		return rects;

	up_RotateCount();
	array<Rect,4> result;
	switch(count)
	{
	case RotateCount::None:
		//た
		result[0]=Rect(new_Pos.X,			 new_Pos.Y			    ,B_SIZE,B_SIZE);
		result[1]=Rect(new_Pos.X,			 new_Pos.Y+(B_SIZE+1)   ,B_SIZE,B_SIZE);
		result[2]=Rect(new_Pos.X+(B_SIZE+1), new_Pos.Y+(B_SIZE+1)   ,B_SIZE,B_SIZE);
		result[3]=Rect(new_Pos.X,			 new_Pos.Y+(B_SIZE+1)*2 ,B_SIZE,B_SIZE);
		break;
	case RotateCount::Once:
		//ぬ
		result[0]=Rect(new_Pos.X,			   new_Pos.Y			,B_SIZE,B_SIZE);
		result[1]=Rect(new_Pos.X+(B_SIZE+1),   new_Pos.Y			,B_SIZE,B_SIZE);
		result[2]=Rect(new_Pos.X+(B_SIZE+1)*2, new_Pos.Y			,B_SIZE,B_SIZE);
		result[3]=Rect(new_Pos.X+(B_SIZE+1),   new_Pos.Y+(B_SIZE+1) ,B_SIZE,B_SIZE);
		break;
	case RotateCount::Twice:
		result[0]=Rect(new_Pos.X+(B_SIZE+1),   new_Pos.Y			  ,B_SIZE,B_SIZE);
		result[1]=Rect(new_Pos.X,			   new_Pos.Y+(B_SIZE+1)	  ,B_SIZE,B_SIZE);
		result[2]=Rect(new_Pos.X+(B_SIZE+1),   new_Pos.Y+(B_SIZE+1)	  ,B_SIZE,B_SIZE);
		result[3]=Rect(new_Pos.X+(B_SIZE+1),   new_Pos.Y+(B_SIZE+1)*2 ,B_SIZE,B_SIZE);
		break;
	case RotateCount::Thrice:
		//で
		result[0]=Rect(new_Pos.X+(B_SIZE+1),   new_Pos.Y			,B_SIZE,B_SIZE);
		result[1]=Rect(new_Pos.X,			   new_Pos.Y+(B_SIZE+1)	,B_SIZE,B_SIZE);
		result[2]=Rect(new_Pos.X+(B_SIZE+1)   ,new_Pos.Y+(B_SIZE+1)	,B_SIZE,B_SIZE);
		result[3]=Rect(new_Pos.X+(B_SIZE+1)*2 ,new_Pos.Y+(B_SIZE+1) ,B_SIZE,B_SIZE);
		break;
	}
	int temp = width;
	width = height;
	height = temp;

	return result;
}

//.    User Coordinate									.			.
// け						.		User Coordinate		 けけ			 け
// け						 けけけ						   け		 けけけ
// けけ.					 け.						   け
//		(BottomX, BottomY)			(BottomX, BottomY)

lShape::lShape(array<Rect,4> &rects)
{
	count=RotateCount::None;
	width=B_SIZE*2+1;
	height=B_SIZE*3+2;

	rects[0]=Rect(INIT_POS_X,			0			 ,B_SIZE,B_SIZE);
	rects[1]=Rect(INIT_POS_X,			B_SIZE+1	 ,B_SIZE,B_SIZE);
	rects[2]=Rect(INIT_POS_X,			(B_SIZE+1)*2 ,B_SIZE,B_SIZE);
	rects[3]=Rect(INIT_POS_X+B_SIZE+1,	(B_SIZE+1)*2 ,B_SIZE,B_SIZE);
}
lShape::~lShape() {}
array<Rect,4>& lShape::Rotate(array<Rect,4> &rects,int PosX, int PosY)
{
	_rotate(PosX,PosY);

	if( new_Pos.X<5 || (new_Pos.X+width)>B_X_NUM*(B_SIZE+1)-10 || new_Pos.Y<5 || (new_Pos.Y+height)>(B_Y_NUM)*(B_SIZE+1)-10 )
		return rects;

	up_RotateCount();
	array<Rect,4> result;
	switch(count)
	{
	case RotateCount::None:
		result[0]=Rect(new_Pos.X,			 new_Pos.Y			    ,B_SIZE,B_SIZE);
		result[1]=Rect(new_Pos.X,			 new_Pos.Y+(B_SIZE+1)   ,B_SIZE,B_SIZE);
		result[2]=Rect(new_Pos.X,			 new_Pos.Y+(B_SIZE+1)*2 ,B_SIZE,B_SIZE);
		result[3]=Rect(new_Pos.X+(B_SIZE+1), new_Pos.Y+(B_SIZE+1)*2 ,B_SIZE,B_SIZE);
		break;
	case RotateCount::Once:
		result[0]=Rect(new_Pos.X,			   new_Pos.Y			,B_SIZE,B_SIZE);
		result[1]=Rect(new_Pos.X+(B_SIZE+1)   ,new_Pos.Y			,B_SIZE,B_SIZE);
		result[2]=Rect(new_Pos.X+(B_SIZE+1)*2 ,new_Pos.Y			,B_SIZE,B_SIZE);
		result[3]=Rect(new_Pos.X,			   new_Pos.Y+(B_SIZE+1) ,B_SIZE,B_SIZE);
		break;
	case RotateCount::Twice:
		result[0]=Rect(new_Pos.X,			 new_Pos.Y			    ,B_SIZE,B_SIZE);
		result[1]=Rect(new_Pos.X+(B_SIZE+1), new_Pos.Y				,B_SIZE,B_SIZE);
		result[2]=Rect(new_Pos.X+(B_SIZE+1), new_Pos.Y+(B_SIZE+1)   ,B_SIZE,B_SIZE);
		result[3]=Rect(new_Pos.X+(B_SIZE+1), new_Pos.Y+(B_SIZE+1)*2 ,B_SIZE,B_SIZE);
		break;
	case RotateCount::Thrice:
		result[0]=Rect(new_Pos.X+(B_SIZE+1)*2, new_Pos.Y			,B_SIZE,B_SIZE);
		result[1]=Rect(new_Pos.X,			   new_Pos.Y+(B_SIZE+1)	,B_SIZE,B_SIZE);
		result[2]=Rect(new_Pos.X+(B_SIZE+1)   ,new_Pos.Y+(B_SIZE+1)	,B_SIZE,B_SIZE);
		result[3]=Rect(new_Pos.X+(B_SIZE+1)*2 ,new_Pos.Y+(B_SIZE+1) ,B_SIZE,B_SIZE);
		break;
	}
	int temp = width;
	width = height;
	height = temp;

	return result;
}

///////////////////////////////////////////////////////////////////////////

IMinoShapeFactory::IMinoShapeFactory() {}
IMinoShapeFactory::~IMinoShapeFactory() {}

iShapeFactory::iShapeFactory() {}
iShapeFactory::~iShapeFactory() {}
MinoShape* iShapeFactory::make(array<Rect,4> &rects) const {	return (MinoShape*) new iShape(rects);	}

oShapeFactory::oShapeFactory() {}
oShapeFactory::~oShapeFactory() {}
MinoShape* oShapeFactory::make(array<Rect,4> &rects) const {	return (MinoShape*) new oShape(rects);	}

sShapeFactory::sShapeFactory() {}
sShapeFactory::~sShapeFactory() {}
MinoShape* sShapeFactory::make(array<Rect,4> &rects) const {	return (MinoShape*) new sShape(rects);	}

tShapeFactory::tShapeFactory() {}
tShapeFactory::~tShapeFactory() {}
MinoShape* tShapeFactory::make(array<Rect,4> &rects) const {	return (MinoShape*) new tShape(rects);	}

lShapeFactory::lShapeFactory() {}
lShapeFactory::~lShapeFactory() {}
MinoShape* lShapeFactory::make(array<Rect,4> &rects) const {	return (MinoShape*) new lShape(rects);	}

MinoShapeFactory::MinoShapeFactory()
{
		shape_factories[0] = (IMinoShapeFactory*)(new iShapeFactory());
		shape_factories[1] = (IMinoShapeFactory*)(new oShapeFactory());
		shape_factories[2] = (IMinoShapeFactory*)(new sShapeFactory());
		shape_factories[3] = (IMinoShapeFactory*)(new tShapeFactory());
		shape_factories[4] = (IMinoShapeFactory*)(new lShapeFactory());
}
MinoShape* MinoShapeFactory::make_shape(array<Rect,4> &rects, int num)
{	
	return ( shape_factories[num]->make(rects) );
}
MinoShapeFactory::~MinoShapeFactory()
{
	int tempM = shape_factories.size();
	for(int i=0; i<tempM; ++i)
		delete shape_factories[i];
}
