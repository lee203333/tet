#include<math.h>
#define half(N) floor((N)+0.5)

////////////////////////���� ���ٹ�///////////////////////////

class MinoStack //�÷��� �� ����&���
{
public:
	array<int,B_Y_NUM> color[B_X_NUM]; //none : -1
	//�� �ڽ� modifier�� ģ���� ���
};

void test1(Rect *rects)
{
	//��.
	//���� �Ʒ� ��ǥ//y�� ���� ũ��
	int m1=10;
	for(int i=0; i<4; ++i)
		if( m1 < (rects[i].Y+10) ) m1=rects[i].Y+10;
	//�ش� ��ǥ (n1,m1) //n+10�� ����
	//1
	//stack[n1]�� ���̸� ����
	//���̸� ���� ��ǥ�� ����
	// stack[n1].high > m1�̸� ����
	//<=�̸� �Ұ�
	//2
	//stack[n1].at(m1-1)�� -1�̸� ����

	//.
	// ��
	// <���� ���� //x�� ���� �۴�
	int m2=100;//���ũ��*X�� ��� �ִ� ����
	for(int i=0; i<4; ++i)
		if( m1 > (rects[i].X) ) m1=rects[i].X;
	//�ش� ��ǥ (m2,n2)
	//stack[(m2-1)].at(n2)�� -1�̸� ����
	//�ƴϸ� �Ұ�

	//���� ������> //x�� ���� ũ��
	int m3=10;
	for(int i=0; i<4; ++i)
		if( m3 < (rects[i].X+10) ) m3=rects[i].X+10;
}

//.    User Coordinate
// ��. 
//	   (BottomX,BottomY)

//stack[i].at(j)
//����� ��ǥ�� 10*i, 290-10*j
//�ݿø�(x/10), 29-����(y/10)
//����(1.5)=1 �� ����
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
	//���� �Ʒ� ��ǥ//y�� ���� ũ��
	//bubble sort
	for(int j=0; j<3; ++j)
	{
		for(int i=0; i<(3-j); ++i)
		{
			if(rects[i].Y > rects[i+1].Y) swapRect(rects,i,i+1);
		}
	}

	//y���� ���ٸ� x���� �̹� ���� ��ǥ�� �ٸ� ���� ��.
	//n�� ����.
	int n= width/10;
	int *selected_Index = new int[n];
	selected_Index[0] = 0;

	// i: rects ��ü ��ȸ, j: ��ȸ�ϸ� �� rect ����, 
	//k: �� rects[i]�� i���� ������ ���� ��ȸ
	for(int i= 1, int j=1; i<4 && j<n; ++i)
	{	// i�� �� ������ ���� 
		// j<n�޼� ��, i ��ȸ ���̶� ����
		// i�� ��ȸ�� �����µ� n(<=4)���� �� ���� ���� ���� ����.
		for(int k=0; k<j; ++k)
		{
			if( rects[i].X != rects[( selected_Index[k] )].X)
			{
				selected_Index[j]=i;
				++j;
			}
		}
	}
	
	//stack[n1].at(m1-1)�� -1�̸� ����
	bool result = true;
	for(int i=0; i<n; ++i)
	{
		int stack_i=(int)half( (rects[( selected_Index[i] )].X)*0.1);
		int stack_j= 29 - ((rects[( selected_Index[i] )].Y)/10);

		if( stack[stack_i].at(stack_j-1) != -1 )
			result=false;
	}//�ϳ��� false�� ����� false

	delete []selected_Index;
	return result;
}
