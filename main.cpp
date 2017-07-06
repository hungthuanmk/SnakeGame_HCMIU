#include <iostream>
#include <stdio.h>
#include <stdlib.h>  // to use system function
#include <conio.h>   // to use kbkit
#include <windows.h> // to make gotoXY
#include <time.h>
#include <vector>    // to build Snake
#include <tchar.h>

#define version "0.3beta"
#define Debug   false
#define ConsoleTitles "IU Snake - By Xuan Tung and HTML *** Updated: 06/07/2017"

#define W       40   //Screen Width
#define H       20   //Screen Height
#define scrX    5    //Screen LeftTop X
#define scrY    2    //Screen LeftTop Y

#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_LEFT    75
#define KEY_RIGHT   77

#define foodIcon        254
#define snakeHeadIcon   178
#define snakeTailIcon   176

#define defaultColor     15
#define snakeHeadColor   2
#define snakeTailColor   14

#define MAX_TAIL (W-2)*(H-2)

/*
 +Name         | Value
 +             |
 +Black        |   0
 +Blue         |   1
 +Green        |   2
 +Cyan         |   3
 +Red          |   4
 +Magenta      |   5
 +Brown        |   6
 +Light Gray   |   7
 +Dark Gray    |   8
 +Light Blue   |   9
 +Light Green  |   10
 +Light Cyan   |   11
 +Light Red    |   12
 +Light Magenta|   13
 +Yellow       |   14
 +White        |   15
 +*/

using namespace std;

char screen[H+1][W+1] = {' '};
int zone[H+1][W+1] = {0};

int score = 0, snakeX = (W/2), snakeY = (H/2), foodX = 0, foodY = 0, gameSpeed = 40, timer = 0;
int numTails = 1;

vector <int> tailX, tailY;

char direct ='S';
bool gameOver = false;
bool gameStart = false;
/*---------------Header--------------------*/
void foodSpawn();
void infoBoard();

/*---------------RootFunc------------------*/
// This Function set cursor to (x,y)
void gotoxy(int x, int y)
{
    static HANDLE hi = NULL;
    if(!hi)
    hi = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(hi,c);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(wHnd, &cursorInfo);
    cursorInfo.bVisible = showFlag;        // set the cursor visibility
    SetConsoleCursorInfo(wHnd, &cursorInfo);
}

void SetTextColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
                        //We use csbi for the wAttributes word.
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
                    //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void ConsoleSetup ()
{
    HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);    // Write on console
    HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);    // Read from console
    CONSOLE_CURSOR_INFO cursorInfo;

    // Change init color
    SetTextColor(defaultColor);

    // Remove Cursor
    ShowConsoleCursor(false);
    /*GetConsoleCursorInfo(wHnd, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(wHnd, &cursorInfo);*/
    // Change Title

    SetConsoleTitle(TEXT(ConsoleTitles));

    SetConsoleOutputCP(437);

    // Resize setup

    SMALL_RECT windowSize = {0, 0, 80, 50};

    // Resize screen

    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

    // Resize buffer
    COORD bufferSize = {80, 50};
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    // Set default code page
    SetConsoleOutputCP(487);
}



/*---------------InitFunc------------------*/
// Make Danger border and zone
void makeDangerBorder()
{
    // Top
    for (int x=0; x<W; x++)
    {
        screen[0][x] = char(205);
        zone[0][x] = 1;
    }
    // Left
    for (int y=0; y<H; y++)
    {
        screen[y][0] = char(186);
        zone[y][0] = 1;
    }
    // Bottom
    for (int x=0; x<W; x++)
    {
        screen[H][x] = char(205);
        zone[H][x] = 1;
    }
    // Right
    for (int y=0; y<H; y++)
    {
        screen[y][W] = char(186);
        zone[y][W] = 1;
    }
    // TopLeft
    screen[0][0] = char(201); zone[0][0]=1;
    // TopRight
    screen[0][W] = char(187); zone[0][W]=1;
    // BottomLeft
    screen[H][0] = char(200); zone[H][0]=1;
    // BottomRight
    screen[H][W] = char(188); zone[H][W]=1;
}

// Safezone Border
void makeSafeBorder()
{
    // Top
    for (int x=0; x<W; x++) screen[0][x] = char(196);
    // Left
    for (int y=0; y<H; y++) screen[y][0] = char(179);
    // Bottom
    for (int x=0; x<W; x++) screen[H][x] = char(196);
    // Right
    for (int y=0; y<H; y++) screen[y][W] = char(179);
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
    if (snakeX == 0 && zone[snakeY][snakeX]!=1)
    {
        screen[snakeY][snakeX]=char(179);
        snakeX = W-1;
    }
    // Bot side
    if (snakeY == H && zone[snakeY][snakeX]!=1)
    {
        screen[snakeY][snakeX] = char(196);
        snakeY = 1;
    }
    // Top side
    if (snakeY == 0 && zone[snakeY][snakeX]!=1)
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
    gotoxy(scrX+W+5,scrY);
    cout << char(201) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205) << char(205);
    if (score>=10) cout << char(205);     // I sure that you can't have more then 100000 so no need to build a numCheck function :))
    if (score>=100) cout << char(205);
    if (score>=1000) cout << char(205);
    if (score>=10000) cout << char(205);
    if (score>=100000) cout << char(205);
    cout << char(187);

    gotoxy(scrX+W+5,scrY+1);
    cout << char(186) << "Score: "<< score << char(186);

    gotoxy(scrX+W+5,scrY+2);
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

    gotoxy(70,Yline);
    cout << "IU Snake ver " << version;
    Yline++;

    gotoxy(70,Yline);
    cout << "Score: " << score;
    Yline++;

    gotoxy(70,Yline);
    cout << "Num of tails: " << numTails;
    Yline++;

    gotoxy(70,Yline);
    cout << "foodX " << foodX << " foodY " << foodY ;
    Yline++;

    gotoxy(70,Yline);
    cout << "numTail " << numTails;
    Yline++;

    gotoxy(70,Yline);
    cout << "Time " << timer;
    Yline++;
}

void drawScreen(){
    for (int i=0; i<=H; i++)
    {
        gotoxy(scrX,scrY+i);
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
    char tempDir;
    if (_kbhit()) //Keyboard Hit
    {
        int kbKey = _getch();
        if (kbKey == 'A' || kbKey == 'a' || kbKey == KEY_LEFT)
            tempDir = 'L';
        if (kbKey == 'S' || kbKey == 's' || kbKey == KEY_DOWN)
            tempDir = 'D';
        if (kbKey == 'D' || kbKey == 'd' || kbKey == KEY_RIGHT)
            tempDir = 'R';
        if (kbKey == 'W' || kbKey == 'w' || kbKey == KEY_UP)
            tempDir = 'U';
        //printf("%d",'a');
     //   if (direct == 'S' && tempDir != 'L')
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
        foodX = rand()%W;
        foodY = rand()%H;
    }
    while (zone[foodY][foodX]!=0 || (foodX==snakeX && foodY==snakeY) || (foodX==0) || (foodY==0));

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
    else
    {
        makeSnake();
        drawScreen();
    }


}

/*
------------------------------------------------
------------------------------------------------
------------------UserInterface-----------------
------------------------------------------------
------------------------------------------------
*/

void startScreen ()
{

}

void mapSelect ()
{

}

void playScreen ()
{
    init();
    while (gameOver!=true)
        {
            draw();
        }
}

void resultScreen ()
{
}

/*---------------MainFunc--------------------*/
int main()
{
    playScreen();
    getch();
    return 0;
}
