#include<math.h>
#define half(N) floor((N)+0.5)

#include"MinoCommand.h"

void SingleMinoCommand::SetSingleMino(SingleMino *single_mino)
{
	singleMino=single_mino;
}

bool SingleMinoCommand::call(Action act, int amount) const
{
	array<Rect,4> rects;
	rects.fill(Rect(0,0,0,0));
	switch(act)
	{
	case Action::rotate:
		rects=singleMino->Rotate();
		if(stackM.CheckMino(rects,singleMino->color)) singleMino->SetRects(rects);
		else
			for(int i=0; i<3; ++i) singleMino->shape->up_RotateCount();
		return true;
	case Action::move_x:
		rects=singleMino->MoveX(amount);
		if(stackM.CheckMino(rects,singleMino->color)) singleMino->SetRects(rects);
		return true;
	case Action::move_y:
		rects=singleMino->MoveY(amount);
		if(stackM.CheckMino(rects,singleMino->color)) singleMino->SetRects(rects);
		return true;
	}
	return true;
}
//SingleMino single;
//StackModifier stack;
//SingleMinoCommand cmd( single. stack);
//cmd.call(Action::rotate, 0);
