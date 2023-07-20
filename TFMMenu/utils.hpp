#include <windows.h>
#include <iostream>

#define log( format, ... ) printf( "[ TFMMenu ]: " format "\n", ##__VA_ARGS__ )


namespace Utils
{
	POINT GetMousePosition();
}