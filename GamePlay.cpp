#ifndef DECLARATION_H_INCLUDED
    #include "Declaration.h"
#endif // DECLARATION_H_INCLUDED

#ifndef CONSOLEAPI_H_INCLUDED
    #include "ConsoleAPI.h"
#endif // CONSOLEAPI_H_INCLUDED

#ifndef GAMEPLAY_H_INCLUDED
    #include "GamePlay.h"
#endif // GAMEPLAY_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>

using namespace std;

extern char version[];

const int W = 40;   //Screen Width
const int H = 20;   //Screen Height
const int scrX = 5;    //Screen LeftTop X
const int scrY = 2;    //Screen LeftTop Y

// VARIABLES

char screen[H+1][W+1] = {' '};
int zone[H+1][W+1] = {0};

int score = 0, snakeX = (W/2), snakeY = (H/2), foodX = 0, foodY = 0, gameSpeed = 40, timer = 0;
int numTails = 1;

vector <int> tailX, tailY;

char direct ='S';
bool gameOver = false;
bool gameStart = false;

void makeDangerBorder()
{
    // Top
    for (int x = 0; x < W; x++)
    {
        screen[0][x] = char(205);
        zone[0][x] = 1;
    }
    // Left
    for (int y = 0; y < H; y++)
    {
        screen[y][0] = char(186);
        zone[y][0] = 1;
    }
    // Bottom
    for (int x = 0; x < W; x++)
    {
        screen[H][x] = char(205);
        zone[H][x] = 1;
    }
    // Right
    for (int y = 0; y < H; y++)
    {
        screen[y][W] = char(186);
        zone[y][W] = 1;
    }
    // TopLeft
    screen[0][0] = char(201);
      zone[0][0] = 1;
    // TopRight
    screen[0][W] = char(187);
      zone[0][W] = 1;
    // BottomLeft
    screen[H][0] = char(200);
      zone[H][0] = 1;
    // BottomRight
    screen[H][W] = char(188);
      zone[H][W] = 1;
}

// Safezone Border
void makeSafeBorder()
{
    // Top
    for (int x = 0; x < W; x++)
        screen[0][x] = char(196);
    // Left
    for (int y = 0; y < H; y++)
        screen[y][0] = char(179);
    // Bottom
    for (int x = 0; x < W; x++)
        screen[H][x] = char(196);
    // Right
    for (int y = 0; y < H; y++)
        screen[y][W] = char(179);
    // TopLeft
    screen[0][0] = char(218);
    // TopRight
    screen[0][W] = char(191);
    // BottomLeft
    screen[H][0] = char(192);
    // BottomRight
    screen[H][W] = char(217);
}

void safeBorderLogic()
{
    // Left side
    if (snakeX == W && zone[snakeY][snakeX] != 1)
    {
        screen[snakeY][snakeX] = char(179);
        snakeX = 1;
    }
    // Right side
    if (snakeX == 0 && zone[snakeY][snakeX] != 1)
    {
        screen[snakeY][snakeX]=char(179);
        snakeX = W-1;
    }
    // Bot side
    if (snakeY == H && zone[snakeY][snakeX] != 1)
    {
        screen[snakeY][snakeX] = char(196);
        snakeY = 1;
    }
    // Top side
    if (snakeY == 0 && zone[snakeY][snakeX] != 1)
    {
        screen[snakeY][snakeX] = char(196);
        snakeY = H-1;
    }
}

// 0 = safe
// 1 = dangerous

// Setup process
void init()
{
    ConsoleSetup();

    //makeDangerBorder();
    makeSafeBorder();
    infoBoard();

    tailX.insert(tailX.begin(),snakeX-2);
    tailY.insert(tailY.begin(),snakeY);

    tailX.insert(tailX.begin(),snakeX-1);
    tailY.insert(tailY.begin(),snakeY);

    foodSpawn();
}

/*---------------BackEnd--------------------*/
void infoBoard ()
{
    goToXY(scrX+W+5,scrY);
    cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205);
    if (score>=10) cout << char(205);     // I am sure that you can't have more than 100000 so no need to build a numCheck function :))
    if (score>=100) cout << char(205);
    if (score>=1000) cout << char(205);
    if (score>=10000) cout << char(205);
    if (score>=100000) cout << char(205);
    cout << char(187);

    goToXY(scrX+W+5,scrY+1);
    cout << char(186) << "Score: "<< score << char(186);

    goToXY(scrX+W+5,scrY+2);
    cout << char(200) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205);
    if (score>=10) cout << char(205);
    if (score>=100) cout << char(205);
    if (score>=1000) cout << char(205);
    if (score>=10000) cout << char(205);
    if (score>=100000) cout << char(205);
    cout << char(188);
}

void debug ()
{
    int Yline=16;

    goToXY(70,Yline);
    cout << "IU Snake ver " << version;
    //cout << "IU Snake ver 0.4b";
    Yline++;

    goToXY(70,Yline);
    cout << "Score: " << score;
    Yline++;

    goToXY(70,Yline);
    cout << "Num of tails: " << numTails;
    Yline++;

    goToXY(70,Yline);
    cout << "foodX " << foodX << " foodY " << foodY ;
    Yline++;

    goToXY(70,Yline);
    cout << "numTail " << numTails;
    Yline++;

    goToXY(70,Yline);
    cout << "Time " << timer;
    Yline++;
}

void drawScreen()
{
    for (int i=0; i<=H; i++)
    {
        goToXY(scrX,scrY+i);
        for (int j=0; j<=W; j++)
         {
            switch (screen[i][j])
            {
                case char(snakeHeadIcon):
                {
                    SetTextColor(snakeHeadColor);
                    cout << screen[i][j];
                    SetTextColor(defaultColor);
                    break;
                }
                case char(snakeTailIcon):
                {
                    SetTextColor(snakeTailColor);
                    cout << screen[i][j];
                    SetTextColor(defaultColor);
                    break;
                }
                case char(foodIcon):
                {
                    SetTextColor(12);
                    cout << screen[i][j];
                    SetTextColor(defaultColor);
                    break;
                }
                default:
                cout << screen[i][j];
            }

        }
    }
}

// getKey --> snakeMove
void getKey()
{
    char tempDir = ' ';
    if (_kbhit()) //Keyboard Hit
    {
        int kbKey = _getch();
        if (kbKey == 'A' || kbKey == 'a')
            tempDir = 'L';
        else
        if (kbKey == 'S' || kbKey == 's')
            tempDir = 'D';
        else
        if (kbKey == 'D' || kbKey == 'd')
            tempDir = 'R';
        else
        if (kbKey == 'W' || kbKey == 'w')
            tempDir = 'U';
        else
        if (kbKey == 0 || kbKey == 224)
        {
            char tempKB = _getch();
            switch (tempKB)
            {
                case KEY_LEFT:
                    tempDir = 'L';
                    break;
                case KEY_DOWN:
                    tempDir = 'D';
                    break;
                case KEY_RIGHT:
                    tempDir = 'R';
                    break;
                case KEY_UP:
                    tempDir = 'U';
                    break;
            }

        }
        //   printf("%d",'a');
        //   if (direct == 'S' && tempDir != 'L')
        if (tempDir != ' ')
            gameStart = true;
    }

    if (
        (tempDir=='D' && direct!='U') ||
        (tempDir=='U' && direct!='D') ||
        (tempDir=='L' && direct!='R') ||
        (tempDir=='R' && direct!='L')
        )
    direct=tempDir;
}

void snakeMove()
{
    switch (direct)
        {
        case 'L':
            snakeX--;
            break;
        case 'R':
            snakeX++;
            break;
        case 'U':
            snakeY--;
            break;
        case 'D':
            snakeY++;
            break;
        }
    //fflush(stdin);
}

void makeSnake()
{
    for (int i = 0; i <= numTails-1; i++) // Tail
    {
        screen[tailY[i]][tailX[i]] = char(snakeTailIcon);
        zone[tailY[i]][tailX[i]] = 1;
    }
    screen[snakeY][snakeX] = char(snakeHeadIcon); //Head
}

void deleteSnake()
{
    screen[snakeY][snakeX] = ' ';
}
// Food Spawn (Fail)
void foodSpawn()
{
    do
    {
        srand(foodX + foodY);
        foodX = rand() % W;
        foodY = rand() % H;
    }
    while (zone[foodY][foodX] !=0 || (foodX==snakeX && foodY==snakeY) || (foodX==0) || (foodY==0));

    screen[foodY][foodX] = char(foodIcon);
}
// Tail

void saveTail ()
{
    tailX.insert(tailX.begin(),snakeX);
    tailY.insert(tailY.begin(),snakeY);
    //deleteTail
    while (tailX.size()>numTails || tailY.size()>numTails)
    {
        screen[tailY[tailY.size()-1]][tailX[tailX.size()-1]]=' ';
        zone[tailY[tailY.size()-1]][tailX[tailX.size()-1]]=0;
        tailX.pop_back();
        tailY.pop_back();
    }
}

// Game Logical
void logic()
{
    safeBorderLogic();

    if (snakeX==foodX && snakeY==foodY)
    {
        score+=10;
        numTails++;

        foodSpawn();
    }

    if (zone[snakeY][snakeX]==1)
        gameOver=true;
}
// This draw
void draw()
{
    getKey();

    if (gameStart)
    {

        snakeMove();
        makeSnake();

        //makeTail();

        logic();
        drawScreen();

        deleteSnake();

        saveTail();

        timer += gameSpeed;

        Sleep(gameSpeed);
        infoBoard();
        if (Debug)
            debug();
    }
    else //Initial screen
    {
        makeSnake();
        drawScreen();
    }
}
