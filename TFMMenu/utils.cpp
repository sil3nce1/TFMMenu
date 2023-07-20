#include "utils.hpp"


POINT Utils::GetMousePosition()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(GetForegroundWindow(), &p);
	p.x -= 320;
	p.y -= 79;
	return p;
}