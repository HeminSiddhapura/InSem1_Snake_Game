#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Game configuration constants
const int WIDTH = 75;
const int HEIGHT = 25;
const char WALL_CHAR = '#';
const char SNAKE_HEAD_CHAR = 'O';
const char SNAKE_BODY_CHAR = 'o';
const char FOOD = '*';

// Directions for movement
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

// Game variables
int snakeX, snakeY, foodX, foodY, score;
int snakeTailX[100], snakeTailY[100], tailLength;
Direction dir;
bool gameOver;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Utility functions
void SetCursorPosition(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

void HideCursor() 
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void SetColor(int color) 
{
    SetConsoleTextAttribute(hConsole, color);
}

// Game setup
void StartGame() 
{
    srand(static_cast<unsigned>(time(0)));
    gameOver = false;
    dir = STOP;
    snakeX = WIDTH / 2;
    snakeY = HEIGHT / 2;
    foodX = (rand() % (WIDTH - 2)) + 1;
    foodY = (rand() % (HEIGHT - 2)) + 1;
    score = 0;
    tailLength =0 ; // Start with 2 tail segments

    // Initialize tail behind the head
    for (int i = 0; i < tailLength; i++) {
        snakeTailX[i] = snakeX - (i + 1);
        snakeTailY[i] = snakeY;
    }
    HideCursor();
}

// Render the game board
void Playground() 
{
    SetCursorPosition(0, 0);

    // Top wall
    for (int i = 0; i < WIDTH + 2; i++) cout << WALL_CHAR;
    cout << endl;

    // Board area with snake and food
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) 
        {
            if (j == 0 || j == WIDTH) 
            {
                cout << WALL_CHAR;
            } 
            else if (i == snakeY && j == snakeX) 
            {
                SetColor(10);
                cout << SNAKE_HEAD_CHAR;
            } 
            else if (i == foodY && j == foodX) 
            {
                SetColor(12);
                cout << FOOD;
            } 
            else 
            {
                bool isTail = false;
                for (int k = 0; k < tailLength; k++)
                {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) 
                    {
                        SetColor(14);
                        cout << SNAKE_BODY_CHAR;
                        isTail = true;
                        break;
                    }
                }
                if (!isTail) cout << " ";
            }
        }
        cout << endl;
    }

    // Bottom wall
    for (int i = 0; i < WIDTH + 2; i++) cout << WALL_CHAR;
    cout << endl;

    // Display score
    SetColor(7);
    cout << "Score: " << score << endl;
}

// Handle snake movement
void ProcessInput()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': case 'A': case 75: dir = (dir != RIGHT) ? LEFT : dir; break;
        case 'd': case 'D': case 77: dir = (dir != LEFT) ? RIGHT : dir; break;
        case 'w': case 'W': case 72: dir = (dir != DOWN) ? UP : dir; break;
        case 's': case 'S': case 80: dir = (dir != UP) ? DOWN : dir; break;
        case 'x': gameOver = true; break;
        }
    }
}

// Game logic
void UpdateGameState()
{
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = snakeX;
    snakeTailY[0] = snakeY;
    for (int i = 1; i < tailLength; i++)
    {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
        case LEFT:  snakeX--; break;
        case RIGHT: snakeX++; break;
        case UP:    snakeY--; break;
        case DOWN:  snakeY++; break;
        default:    break;
    }

    if (snakeX < 0 || snakeX >= WIDTH || snakeY < 0 || snakeY >= HEIGHT)
        gameOver = true;

    for (int i = 0; i < tailLength; i++) 
    {
        if (snakeTailX[i] == snakeX && snakeTailY[i] == snakeY)
        {
            gameOver = true;
        }
    }

    if (snakeX == foodX && snakeY == foodY)
    {
        score += 10;
        foodX = (rand() % (WIDTH - 2)) + 1;
        foodY = (rand() % (HEIGHT - 2)) + 1;
        tailLength++;
    }
}

int main()
{
     
        StartGame();
        while (!gameOver)
        {
            Playground();
            ProcessInput();
            UpdateGameState();
            Sleep(100);
        }

        cout << "\nGame Over! Final Score: " << score << endl;
        if (score < 50) cout << "Rank: Beginner\n";
        else if (score < 100) cout << "Rank: Intermediate\n";
        else if (score < 200) cout << "Rank: Expert\n";
        else cout << "Rank: Legend\n";
    return 0;
}
