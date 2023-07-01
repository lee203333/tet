#include<math.h>
#define half(N) floor((N)+0.5)

////////////////////////버린 접근법///////////////////////////

class MinoStack //컬렉션 값 보관&출력
{
public:
	array<int,B_Y_NUM> color[B_X_NUM]; //none : -1
	//각 자식 modifier는 친구로 등록
};

void test1(Rect *rects)
{
	//ㅁ.
	//가장 아래 좌표//y가 가장 크다
	int m1=10;
	for(int i=0; i<4; ++i)
		if( m1 < (rects[i].Y+10) ) m1=rects[i].Y+10;
	//해당 좌표 (n1,m1) //n+10된 값임
	//1
	//stack[n1]의 높이를 조사
	//높이를 절대 좌표로 변경
	// stack[n1].high > m1이면 가능
	//<=이면 불가
	//2
	//stack[n1].at(m1-1)이 -1이면 가능

	//.
	// ㅁ
	// <가장 왼쪽 //x가 가장 작다
	int m2=100;//블록크기*X축 블록 최대 갯수
	for(int i=0; i<4; ++i)
		if( m1 > (rects[i].X) ) m1=rects[i].X;
	//해당 좌표 (m2,n2)
	//stack[(m2-1)].at(n2)가 -1이면 가능
	//아니면 불가

	//가장 오른쪽> //x가 가장 크다
	int m3=10;
	for(int i=0; i<4; ++i)
		if( m3 < (rects[i].X+10) ) m3=rects[i].X+10;
}

//.    User Coordinate
// ㅁ. 
//	   (BottomX,BottomY)

//stack[i].at(j)
//블록의 좌표는 10*i, 290-10*j
//반올림(x/10), 29-내림(y/10)
//내림(1.5)=1 몫만 남김
array<int,30> stack[10];

void swapRect(Rect *rects, int num1, int num2)
	{
		Point temp= Point(rects[num1].X,rects[num1].Y);

		rects[num1].X = rects[num2].X;
		rects[num1].Y = rects[num2].Y;

		rects[num2].X = temp.X;
		rects[num2].Y = temp.Y;
	}
bool checkBottom (Rect *rects, int width)
{
	//가장 아래 좌표//y가 가장 크다
	//bubble sort
	for(int j=0; j<3; ++j)
	{
		for(int i=0; i<(3-j); ++i)
		{
			if(rects[i].Y > rects[i+1].Y) swapRect(rects,i,i+1);
		}
	}

	//y값이 같다면 x값이 이미 가진 좌표와 다른 것을 고름.
	//n개 고른다.
	int n= width/10;
	int *selected_Index = new int[n];
	selected_Index[0] = 0;

	// i: rects 전체 순회, j: 순회하며 고른 rect 개수, 
	//k: 고른 rects[i]의 i값을 저장한 수열 순회
	for(int i= 1, int j=1; i<4 && j<n; ++i)
	{	// i는 한 바퀴만 돈다 
		// j<n달성 시, i 순회 중이라도 정지
		// i의 순회가 끝났는데 n(<=4)개를 다 고르지 못할 일은 없다.
		for(int k=0; k<j; ++k)
		{
			if( rects[i].X != rects[( selected_Index[k] )].X)
			{
				selected_Index[j]=i;
				++j;
			}
		}
	}
	
	//stack[n1].at(m1-1)이 -1이면 가능
	bool result = true;
	for(int i=0; i<n; ++i)
	{
		int stack_i=(int)half( (rects[( selected_Index[i] )].X)*0.1);
		int stack_j= 29 - ((rects[( selected_Index[i] )].Y)/10);

		if( stack[stack_i].at(stack_j-1) != -1 )
			result=false;
	}//하나라도 false면 결과는 false

	delete []selected_Index;
	return result;
}
