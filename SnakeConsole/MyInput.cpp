#include "MyInput.h"

void MyInput::StartInput()
{
	running = true;
	thread_input = std::thread(&MyInput::InputLoop, this);
	thread_input.detach();
}

void MyInput::InputLoop()
{
	while (running) {
		if (GetAsyncKeyState('S') & 0x8000)
		{
			lastKey = 's';
		}else if (GetAsyncKeyState('A') & 0x8000)
		{
			lastKey = 'a';
		}else if (GetAsyncKeyState('D') & 0x8000)
		{
			lastKey = 'd';
		}else if (GetAsyncKeyState('W') & 0x8000)
		{
			lastKey = 'w';
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}

int MyInput::GetLastKeyHit()
{
	return lastKey;
}

MyInput::~MyInput()
{
	std::cout << "Exiting Input";
}
