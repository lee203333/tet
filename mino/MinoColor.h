#pragma once
#include<Windows.h>
#include<map>
using namespace std;

#include<GdiPlus.h>
#pragma comment(lib,"gdiplus")
using namespace Gdiplus;

enum MinoColor
{
	RED,
	YELLOW,
	BLUE
};
class ColorAdapter//MinoColor to GdiPlus::Color
{
	map<MinoColor, Color> map;
public:
	ColorAdapter();
	Color& from(const MinoColor mino_color);
	~ColorAdapter();
};
