#pragma once
#include <iostream>
#include <windows.h>
#include <thread>

class MyInput
{
public:
	~MyInput();
	int GetLastKeyHit();
	void StartInput();
	bool running = false;
private:
	void InputLoop();
	int lastKey = 0;
	std::thread thread_input;
};
