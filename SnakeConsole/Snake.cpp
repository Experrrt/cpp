#include "Snake.h"
//
void Snake::StartGame()
{
    thread_snake = std::thread(&Snake::GameLoop, this);
    thread_snake_draw = std::thread(&Snake::GameDrawLoop, this);
    timer.StartTimer();
    myInput.StartInput();
    thread_snake_draw.detach();
    thread_snake.join();
}

void Snake::Draw()
{
    ClearTerminal();

    timer.PrintTime();
    std::string statsString = " %"+std::to_string(w*2-11)+ "s\n";
    std::string scoreString = "SCORE: " + std::to_string(score - 1);
    printf(statsString.c_str(), scoreString.c_str());

    for (int i = 0; i < w + 1; i++)
    {
        std::cout << "# ";
    }
    std::cout << std::endl;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            tailPrinted = false;
            if (j == 0 || j == w - 1) {
                std::cout << "# ";
            }
            for (size_t b = 0; b < tailX.size() - 1 && tailX.size()!=0 && tailY.size()==tailX.size(); b++)
            {
                if (tailX.at(b) == pX && tailY.at(b) == pY) {
                    running = false;
                }
                else if (tailX.at(b) == j && tailY.at(b) == i) {
                    std::cout << "P ";
                    tailPrinted = true;
                    break;
                }
            }

            if (j == pX && i == pY) {
                std::cout << "D ";
            }
            else if (j == aX && i == aY) {
                std::cout << "A ";
            }
            else if (!tailPrinted) {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < w + 1; i++)
    {
        std::cout << "# ";
    }
    std::cout << std::endl;
}

//int Snake::GetKeyDown() {
//    if (_kbhit())
//    {
//        return _getch();
//    }
//    return -1;
//}

void Snake::GenApplePosition() {
    int randomX;
    int randomY;
    bool colidesTail;
    srand(static_cast<unsigned int>(time(nullptr)));

    do
    {
        colidesTail = false;
        randomX = rand() % (w-1);
        randomY = rand() % h;
        for (size_t b = 0; b < tailX.size() - 1; b++)
        {
            if (tailX.empty())break;
            if (tailX.at(b) == randomX && tailY.at(b) == randomY) {
                colidesTail = true;
            }
        }
    } while ((randomX == pX && randomY == pY) || colidesTail);
    
      aX = randomX;
      aY = randomY;
}

int Snake::CountDelay() {
    int delay = 350 - score * 12;

    if (delay < 150) {
        return 150;
    }
    return delay;
}

void Snake::HandleInput()
{
    int keyDown = myInput.GetLastKeyHit();
    switch (keyDown)
    {
    case 'a':
        if (dir == eDirection::RIGHT)break;
        dir = eDirection::LEFT;
        break;
    case 'd':
        if (dir == eDirection::LEFT)break;
        dir = eDirection::RIGHT;
        break;
    case 'w':
        if (dir == eDirection::DOWN)break;
        dir = eDirection::UP;
        break;
    case 's':
        if (dir == eDirection::UP)break;
        dir = eDirection::DOWN;
        break;
    default:
        break;
    }
}

void Snake::Logic()
{
    switch (dir)
    {
    case eDirection::LEFT:
        pX--;
        break;
    case eDirection::RIGHT:
        pX++;
        break;
    case eDirection::UP:
        pY--;
        break;
    case eDirection::DOWN:
        pY++;
        break;
    default:
        break;
    }

    if (pX >= w - 1) {
        pX = 0;
    }
    else if (pX < 0) {
        pX = w - 2;
    }
    if (pY >= h) {
        pY = 0;
    }
    else if (pY < 0) {
        pY = h - 1;
    }

    if (aX == pX && aY == pY) {
        score++;
        GenApplePosition();
    }
    if (dir != eDirection::STOP) {
        tailX.push_back(pX);
        tailY.push_back(pY);
    }

    if (tailX.size() > (size_t) score && tailY.size() > (size_t) score && tailX.size()!=0) {
        tailX.erase(tailX.begin());
        tailY.erase(tailY.begin());
    }
}

void Snake::GameEndStats()
{
    system("cls");
    std::cout<<"Post game stats:\n";
    timer.PrintTime();
    std::cout << "\nScore: "<<score<<"\n";
    std::cout << "------------\n";
    std::cout << "Enter to exit ";
    
    //input buffer clear
    PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256];
    DWORD ClearingVar2;
    ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), ClearingVar1, 256, &ClearingVar2);
    delete[] ClearingVar1;

    std::cin.ignore();
    std::cin.get();
}

void Snake::GameLoop()
{
    while (running) {
        HandleInput();
        Logic();
        std::this_thread::sleep_for(std::chrono::milliseconds(CountDelay()));
    }
    timer.running = false;
    myInput.running = false;
}

void Snake::GameDrawLoop()
{
    while (running) 
    {
        start = std::chrono::system_clock::now();
        Draw();
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        std::this_thread::sleep_for(std::chrono::milliseconds(calcDelay((int)(elapsed_seconds.count()*1000))));
    }
}

void Snake::ClearTerminal()
{
    COORD cur = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}

int Snake::calcDelay(int elapsed)
{
    int calc = FPSTarget - elapsed;
    if(calc < 0) 
    {
        calc = 0;
    }
    printf("%3d fps", 1000 / (calc + (int)(elapsed_seconds.count() * 1000)));
    return calc;
}

Snake::Snake(int width, int height, int FPSTarget)
{
    Snake::w = width;
    Snake::h = height;
    Snake::FPSTarget = FPSTarget;

    GenApplePosition();
}

Snake::~Snake()
{
    GameEndStats();
    std::cout << "Exiting Snake\n";
}
