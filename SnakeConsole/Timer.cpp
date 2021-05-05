#include "Timer.h"

void Timer :: StartTimer()
{
	running = true;
	thread_timer = std::thread(&Timer::TimerCount, this);
	thread_timer.detach();
}

Timer::~Timer() 
{
	std::cout << "Exiting Timer\n";
}

void Timer::TimerCount()
{
	while (running) {
		Seconds++;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void Timer::PrintTime()
{
	int minutes = Seconds / 60;
	int seconds = Seconds- 60 * minutes;

	printf("Time: %02d:%02d", minutes, seconds);
}




