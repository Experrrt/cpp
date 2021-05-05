#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <chrono>
#define NOMINMAX
#include <windows.h>
#include <memory>
#include "Timer.h"
#include "MyInput.h"


class Snake
{
public:
	Snake(int width, int height, int FPSTarget);
	~Snake();
	void StartGame();
private:
	std::thread thread_snake;
	std::thread thread_snake_draw;
	void Draw();
	void GenApplePosition();
	int CountDelay();
	void HandleInput();
	void Logic();
	void GameLoop();
	void GameEndStats();
	void GameDrawLoop();
	int calcDelay(int elapsed);
	void ClearTerminal();

	int w, h, score = 1, pX = 8, pY = 8, aX, aY, FPSTarget;
	bool tailPrinted = false;
	enum class eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }dir;
	bool running = true;
	std::vector <int> tailX;
	std::vector <int> tailY;
	MyInput myInput;
	Timer timer;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> elapsed_seconds;
};
