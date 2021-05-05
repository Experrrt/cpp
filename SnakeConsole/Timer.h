#pragma once
#include <thread>
#include <iostream>

class Timer
{
public:
	~Timer();
	void StartTimer();
	void PrintTime();
	bool running = false;
private:
	std::thread thread_timer;
	void TimerCount();
	int Seconds = -1;
};


