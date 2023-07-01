#include<math.h>
#define half(N) floor((N)+0.5)

#include"StackMino.h"
#include"SingleMino.h"
#include"MinoCommand.h"

StackMino::StackMino() 
{	
	for(int i=0; i<B_X_NUM; ++i)
		stack[i].fill(-1);
}
	
//그리기 관련
int StackMino::jLength(int i)
{
	int j;
	for(j=B_Y_NUM-1; j>=0 && (stack[i].at(j)==-1) ; --j)
		;
	return j+1;
}

Color& StackMino::GetColor(int i, int j)
{
	C=Color(255,255,255);
	if(stack[i].at(j) == -1)
		return C;
	return adapt.from( (MinoColor)(stack[i].at(j)) );
}

//.    User Coordinate
// ㅁ. 
//	   (BottomX,BottomY)

//stack[i].at(j)
//블록의 좌표는 10*i, 300+10*(1-j)


//				ㅁ //0
//				ㅁ //11
//ㅁㅁㅁㅁ		ㅁ //22
//0,11,22		//29*11= 319	//319-11*j = 11*(29-j)
int StackMino::GetPosX(int i) {	return (B_SIZE+1)*i;	}
int StackMino::GetPosY(int j) {	return (B_SIZE+1)*(B_Y_NUM-1-j);	}


bool StackModifier::CheckMino(array<Rect,4> &rects, MinoColor mColor)
{
	bool bottom = false;
	for(int i=0; i<4; ++i)
	{
		if( rects[i].X<0 || rects[i].X>B_X_NUM*(B_SIZE+1)-10 || rects[i].Y<0 || rects[i].Y>(B_Y_NUM)*(B_SIZE+1)-10 )
			return false;

		int stack_i=(int) rects[i].X/11+half( (rects[i].X%11)*0.09091);
		int stack_j=(int) 29 - (rects[i].Y/11)- half( (rects[i].Y%11)*0.09091);

		if( stack_j < 0)
			return false;
		if( stackMino.stack[stack_i].at(stack_j)!= -1)
			return false;
		//공간은 있지만 바닥에 닿았다면
		if(stack_j == stackMino.jLength(stack_i) )
			bottom=true;
	}
	if(bottom)//하나라도
	{
		InsertMino(rects, mColor);
		return false;
	}
	return true;
}
void StackModifier::InsertMino(array<Rect,4> &rects, MinoColor mColor)
{
	array<int,4> bingoLine;
	for(int i=0; i<4; ++i)
	{
		int stack_i=(int) rects[i].X/11+half( (rects[i].X%11)*0.09091);
		int stack_j= (int) 29 - (rects[i].Y/11)- half( (rects[i].Y%11)*0.09091);
		if(rects[i].X > (B_X_NUM-1)*(B_SIZE+1) ) throw false;

		stackMino.stack[stack_i].at(stack_j) = (int)mColor;
		bingoLine[i]=BingoLine();
	}
	modifier.handle(stackMino, bingoLine);
}


int StackModifier::BingoLine()
{
	for(int j=0; j<B_Y_NUM; ++j)
	{
		for(int i=0;i<B_X_NUM && stackMino.stack[i].at(j)!=-1; ++i)
			if(i==B_X_NUM-1) return j;
	}
	return -1;
}
//빙고처리
//1 2 2 3 3 3 0 0
//1 2 0 3 3 3 0 0
//해당 줄을 0으로 바꾸고
//1 2 3 0 3 3 0 0
//1 2 3 3 0 3 0 0
//1 2 3 3 3 0 0 0
//끝까지 스왑
void StackBingoProcess::SetZero(StackMino& source, int num)
{
	for(int j=0; j<B_X_NUM;++j)
			source.stack[j].at(num)=-1;
}
void StackBingoProcess::Pull(StackMino& source, int num)
{
	for(int i=0; i<B_X_NUM; ++i)
		{
			for(int k=0; k<(B_Y_NUM -num-1); ++k)
			{
				int temp = source.stack[i].at(num+k);
				source.stack[i].at(num+k) = source.stack[i].at(num+1+k);
				source.stack[i].at(num+1+k) =temp;
			}
		}
}
void StackBingoProcess::handle(StackMino& source,array<int,4> &bingoLine )
{
	single->show=false;
	update(single, source);

	for(int i=0; i<4; ++i)
	{
		if(bingoLine[i] != -1)
		{
			SetZero(source, bingoLine[i]);
			update(single, source);
			Sleep(100);

			Pull(source, bingoLine[i]);
			update(single, source);
		}
	}
	Modifier::handle(source,bingoLine);
}
void StackBingoProcess::SetSingleMino(SingleMino *single_mino)
{
	single=single_mino;
}

void SingleResetProcess::handle(StackMino& source,array<int,4> &bingoLine )
{
	bool temp = true;
	//int stack_i=(int) INIT_POS_X/11+half( (INIT_POS_X%11)*0.09091);
	int stack_i = 8;
	for(int i=0; i<3;++i)
		if( source.jLength(stack_i +i) >28) temp= false;
	
	if(temp)
	{
		single->reset();
		if(single->show==false)	single->show=true;
	}
	else
	{
		(*page)=2;//etern로 데려왔음
	}
	Modifier::handle(source,bingoLine);
}
void SingleResetProcess::SetSingleMino(SingleMino *single_mino)
{
	single=single_mino;
}


void ScoreProcess::handle(StackMino& source,array<int,4> &bingoLine )
{
	for(int i=0; i<4; ++i)
	{
		if(bingoLine[i] != -1)
		{
			score+=10;
		}
	}
	Modifier::handle(source,bingoLine);
}

LPWSTR ScoreProcess::GetwScore() 
{
	int digit[4];
	digit[0] = (score/1000);
	digit[1] = (score/100)-digit[0]*10;
	digit[2] = (score/10)-(score/100)*10;
	digit[3] = score%10;//일의 자리수

	for(int i=0; i<4; ++i)
		wScore[i]=(wchar_t)digit[i]+48;

	return wScore;	
}
int ScoreProcess::GetScore() {	return score;	}
