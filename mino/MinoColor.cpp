
#include"MinoColor.h"


ColorAdapter::ColorAdapter()
{
	map[MinoColor::RED]=Color(250,0,0);
	map[MinoColor::YELLOW]=Color(250,250,0);
	map[MinoColor::BLUE]=Color(0,0,250);
}
Color& ColorAdapter::from(const MinoColor mino_color) {	return map[mino_color];		}
ColorAdapter::~ColorAdapter() { }
