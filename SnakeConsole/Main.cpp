#include <iostream>
#include "Timer.h"
#include "Snake.h"
#include "MyInput.h"

int main()
{
	int size, FPSTarger;
	std::cout << "Field size: ";
	std::cin >> size;
	std::cout << "FPS Target: ";
	std::cin >> FPSTarger;
	if (FPSTarger != 0)
	{
		FPSTarger = 1000 / FPSTarger;
	}

	Snake snake(size, size, FPSTarger);
	snake.StartGame();
	
}