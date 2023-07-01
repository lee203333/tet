#include<Windows.h>
#include<stdlib.h>
#include<time.h>

#include<GdiPlus.h>
#pragma comment(lib,"gdiplus")
using namespace Gdiplus;

#include"mino.h"

#define SPEED 2

#define ID_START 100
#define ID_TIMER 2

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_Inst;
LPSTR lpszClass = "TETRIS";
HWND hWndMain;

static int Page;
static ScoreProcess Score;
//////////////////////////더블 버퍼링/////////////////////////////////
CachedBitmap* pCBit;
void update(SingleMino *single, StackMino &stack)
{
	Graphics G(hWndMain);
	RECT crt;
	GetClientRect(hWndMain,&crt);
	
	Bitmap* pBit = new Bitmap(crt.right, crt.bottom, &G);
	Graphics* memG = new Graphics(pBit);
	memG->FillRectangle(&SolidBrush(Color(255,255,255)),0,0,crt.right,crt.bottom);
	
	//----------그리기----------//
	//memG에 그림 그림
	if(Page ==0)
	{
		Pen startPen(Color(0,0,0),2);
		SolidBrush startBR1(Color(70,250,255));
		SolidBrush startBR2(Color(150,0,0));
		SolidBrush startBR3(Color(0,200,0));
		SolidBrush startBR4(Color(250,250,0));		
		//T
		memG->FillRectangle(&startBR2,10,100,30,5);
		memG->FillRectangle(&startBR2,22,100,5,35);
		//E
		memG->FillRectangle(&startBR3,50,100,25,5);
		memG->FillRectangle(&startBR3,50,115,25,5);
		memG->FillRectangle(&startBR3,50,130,25,5);
		memG->FillRectangle(&startBR3,50,100,5,30);
		//t
		memG->DrawRectangle(&startPen,92,105,6,30);
		memG->DrawRectangle(&startPen,83,110,26,5);
		memG->DrawRectangle(&startPen,92,130,15,5);
		//R
		memG->FillRectangle(&startBR4,120,100,25,5);
		memG->FillRectangle(&startBR4,120,100,5,35);
		memG->FillRectangle(&startBR4,140,120,5,15);
		memG->FillRectangle(&startBR4,120,118,15,5);
		Point Rpoints[4]={Point(133,118),Point(145,105),Point(147,108),Point(140,120)};
		memG->FillPolygon(&startBR4,Rpoints,4);
		//i
		memG->FillRectangle(&startBR1,160,105,5,5);
		memG->FillRectangle(&startBR1,160,115,5,20);
		//S
		Point Spoints1[4]={Point(195,97),Point(195,104),Point(204,114),Point(209,110)};
		memG->DrawPolygon(&startPen,Spoints1,4);
		Point Spoints2[4]={Point(195,97),Point(195,104),Point(180,114),Point(180,108)};
		memG->DrawPolygon(&startPen,Spoints2,4);
		Point Spoints3[4]={Point(200,128),Point(203,123),Point(186,110),Point(180,114)};
		memG->DrawPolygon(&startPen,Spoints3,4);
		Point Spoints4[4]={Point(203,123),Point(200,119),Point(194,130),Point(194,138)};
		memG->DrawPolygon(&startPen,Spoints4,4);
		Point Spoints5[4]={Point(178,128),Point(180,123),Point(194,131),Point(194,138)};
		memG->DrawPolygon(&startPen,Spoints5,4);
	}
	else
	{
		//Page ==1 || Page ==2
		Pen pen1(Color(0,0,0));
		memG->DrawLine(&pen1,B_X_NUM*(B_SIZE+1),0,B_X_NUM*(B_SIZE+1),(B_Y_NUM)*(B_SIZE+1));
		memG->DrawLine(&pen1,0,(B_Y_NUM)*(B_SIZE+1),B_X_NUM*(B_SIZE+1),(B_Y_NUM)*(B_SIZE+1));

		Font font(L"굴림",10);
		PointF fontP(10.0,(B_Y_NUM)*(B_SIZE+1)+10.0);
		SolidBrush fontBrush(Color(0,0,0));
		memG->DrawString(L"SCORE :",-1,&font, PointF(10.0,(B_Y_NUM)*(B_SIZE+1)+10.0), &fontBrush);
		memG->DrawString(Score.GetwScore(),4,&font, PointF(90.0,(B_Y_NUM)*(B_SIZE+1)+10.0), &fontBrush);
		for(int i=0; i< B_X_NUM; ++i)
		{
			for(int j=0; j< stack.jLength(i); ++j)
			{
				SolidBrush stackBrush( stack.GetColor(i,j));
				memG->FillRectangle( &stackBrush, stack.GetPosX(i), stack.GetPosY(j),B_SIZE,B_SIZE);
			}
		}
		if(single == nullptr || Page==2)
		{
			Page = 2;//게임오버
			SolidBrush overBrush(Color(150,0,0,0));
			memG->FillRectangle( &overBrush,0,0, B_X_NUM*(B_SIZE+1)+10, (B_Y_NUM)*(B_SIZE+1)+60);
			Font overFT(L"굴림",20,FontStyle::FontStyleBold);
			SolidBrush overBR(Color(255,255,255));
			memG->DrawString(L"GAME OVER",-1,&overFT, PointF(20.0,100.0), &overBR);
		}
		else				//Page ==1
		{
			if( single->show ==true)//nullptr는 접근 금지
			{
				SolidBrush singleBrush( single->GetColor());
				memG->FillRectangles( &singleBrush, single->GetRects(), 4);
			}
		}
	}
	//-----------------------------------//
	if (pCBit) delete pCBit;
	pCBit = new CachedBitmap(pBit, &G);
	
	delete pBit;
	delete memG;
	InvalidateRect(hWndMain, NULL, FALSE);
}

void Paint(HDC hdc,SingleMino *single, StackMino &stack, SingleMinoCommand &cmd)
{
	Graphics G(hdc);
	if (pCBit == NULL)
	{
		if(single->show==false)	single->show=true;
		update(single,stack);
	}
	G.DrawCachedBitmap(pCBit, 0, 0);
}
/////////////////////////////////////////////////
class CGdiPlusStarter
{
private:
	ULONG_PTR m_gpToken;

public:
	bool m_bSuccess;
	CGdiPlusStarter()
	{
		GdiplusStartupInput gpsi;
		m_bSuccess = (GdiplusStartup(&m_gpToken, &gpsi, NULL) == Ok);
	}
	~CGdiPlusStarter()
	{
		GdiplusShutdown(m_gpToken);
	}

};
CGdiPlusStarter g_gps;
//////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_Inst = hInstance;
	/////////////////////////////////////////
	ULONG_PTR gpToken;
	GdiplusStartupInput gpsi;
	if (g_gps.m_bSuccess == FALSE)
	{
		MessageBox(NULL, TEXT("GDI+라이브러리 초기화 불가"), TEXT("알림"), MB_OK);
		return 0;
	}
	//////////////////////////////////////////
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;

	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPED | WS_SYSMENU , 500, 200, B_X_NUM*(B_SIZE+1)+10, (B_Y_NUM)*(B_SIZE+1)+60, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	WndClass.cbWndExtra=sizeof(DWORD);
	
	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

HWND StartButton;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static SingleMino *singleMino;
	static StackMino stackMino;

	static StackModifier stackModifier( stackMino); //Observable이라서
	static StackBingoProcess Bprocess(singleMino);
	static SingleResetProcess Rprocess(singleMino, &Page);
	static SingleMinoCommand cmd( singleMino, stackMino, stackModifier);
	
	switch (iMessage)
	{
	case WM_CREATE:
		hWndMain = hWnd;
		Page=0;
		StartButton = CreateWindow(TEXT("button"), TEXT("시작"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 70, 170, 80, 40, hWndMain, (HMENU)ID_START, g_Inst, NULL);
		srand( (unsigned int)time(NULL));//실행마다 난수생성이 다르게 되기위한 시드 설정
		singleMino= new SingleMino();
		Bprocess.SetSingleMino(singleMino);
		Rprocess.SetSingleMino(singleMino);
		cmd.SetSingleMino(singleMino);
		stackModifier.add((Modifier*)&Bprocess);
		stackModifier.add((Modifier*)&Rprocess);
		stackModifier.add((Modifier*)&Score);//제일 위에, Page 밑에
		SetTimer(hWnd,ID_TIMER,50,NULL);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd,ID_TIMER);
		if(singleMino != nullptr) delete singleMino;
		PostQuitMessage(0);
		return 0;
	case WM_TIMER:
		try
		{
			if(Page==1 && singleMino!= nullptr )
			{
				cmd.call(Action::move_y,SPEED*1);
				if(singleMino->GetPosX()<-100 ||singleMino->GetPosX()>300 ||singleMino->GetPosY()<-100 || singleMino->GetPosX()>400) 
					if(singleMino != nullptr )throw singleMino;
			}
		}
		catch(const bool e)
		{

		}
		catch(SingleMino *e)
		{
			singleMino->reset();
			Bprocess.SetSingleMino(singleMino);
			Rprocess.SetSingleMino(singleMino);
			cmd.SetSingleMino(singleMino);
		}
		update(singleMino,stackMino);
		return 0;
	case WM_COMMAND:
		if(Page==0)
		{
			switch( LOWORD(wParam))
			{
			case ID_START:
				ShowWindow(StartButton, SW_HIDE);
				Page=1;
				break;
			}
		}
		return 0;
	case WM_KEYDOWN:
		if(Page==1 && singleMino!=nullptr )
		{
			switch(wParam)
			{
			case VK_RIGHT:
				cmd.call(Action::move_x,3);
				update(singleMino,stackMino);
				break;
			case VK_LEFT:
				cmd.call(Action::move_x,-3);
				update(singleMino,stackMino);
				break;
			case VK_SPACE:
				cmd.call(Action::rotate,0);
				update(singleMino,stackMino);
				break;
			}
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Graphics G(hdc);
		Paint(hdc, singleMino, stackMino, cmd);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
