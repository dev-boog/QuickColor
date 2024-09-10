#include <iostream>
#include <thread>

#include <windows.h>

#include "window.h"
#include "color.h"

int main()
{
	std::thread color_thread(color::thread);
	color_thread.detach();

	while (!GetAsyncKeyState(VK_DELETE)) 
	{
		window::render();
	}

	return 0;
}