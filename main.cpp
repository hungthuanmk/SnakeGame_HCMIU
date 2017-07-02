/*
---------LOG-----------
- First C/C++ class (26/06/2017), project game making: Caro, Sudoku, Snake
--> Snake challenge accepted!
-------BUILD LOG-------
******26/06/2017*******
- Research snake game making on internet
- Build a wall around
******27/06/2017*******
- Build a snake head can move around and snake properties
- Food spawning (a big bug)
******28/06/2017*******
- Big bug removed (still some)
- Snake tail build (luckily! just some bug)
******29/06/2017*******
- IU Snake ver 0.01beta completed with ONE bug (go left on the start will kill snake :) )
    Feature:
    - A simple snake game
    - Snake can move around map, eat food, die when touch wall or eat himself :)
    - Snake move vertical fasterrrrr...
    - Scoring system included
    - No annoying cursor mess up
    - No long delay
    - Just 1.0 MB :)
******30/06/2017*******
- IU Snake ver 0.02beta updated
    - Snake can go through safe border (no bug detected)
    - Score board added

*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>  // to use system function
#include <conio.h>   // to use kbkit
#include <windows.h> // to make gotoXY
#include <time.h>
#include <vector>    // to build Snake
#include <tchar.h>

#define W 40   //Screen Width
#define H 20   //Screen Height
#define scrX 5    //Screen LeftTop X
#define scrY 2    //Screen LeftTop Y

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define foodIcon 111
#define snakeHeadIcon 178
#define snakeTailIcon 176

#define MAX_TAIL (W-2)*(H-2)

using namespace std;

char screen[H+1][W+1]={' '};
int zone[H+1][W+1]={0};

int score=0, snakeX=(W/2), snakeY=(H/2), foodX=0, foodY=0, gameSpeed=50, timer=0;
int numTails=2;

vector <int> tailX, tailY;



char direct='S';
bool gameOver=false;
bool gameStart=false;
/*---------------Header--------------------*/
void foodSpawn();
void infoBoard ();

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

void ConsoleSetup ()
{
    HANDLE wHnd=GetStdHandle(STD_OUTPUT_HANDLE);    // Write on console
    HANDLE rHnd=GetStdHandle(STD_INPUT_HANDLE);    // Read from console
    CONSOLE_CURSOR_INFO cursorInfo;

    // Remove Cursor
    ShowConsoleCursor(false);
    /*GetConsoleCursorInfo(wHnd, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(wHnd, &cursorInfo);*/
    // Change Title

    SetConsoleTitle(TEXT("IU Snake 0.02b - By Xuan Tung and HTML *** Updated: 30/06/2017"));

    // Resize setup

    SMALL_RECT windowSize = {0, 0, 80, 50};

    // Resize screen

    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

    // Resize buffer
    COORD bufferSize = {80, 50};
    SetConsoleScreenBufferSize(wHnd, bufferSize);
}

/*---------------InitFunc------------------*/
void makeDangerBorder()
{
    // Top
    for (int x=0; x<W; x++)
    {
        screen[0][x]=char(205);
        zone[0][x]=1;
    }
    // Left
    for (int y=0; y<H; y++)
    {
        screen[y][0]=char(186);
        zone[y][0]=1;
    }
    // Bottom
    for (int x=0; x<W; x++)
    {
        screen[H][x]=char(205);
        zone[H][x]=1;
    }
    // Right
    for (int y=0; y<H; y++)
    {
        screen[y][W]=char(186);
        zone[y][W]=1;
    }
    // TopLeft
    screen[0][0]=char(201); zone[0][0]=1;
    // TopRight
    screen[0][W]=char(187); zone[0][W]=1;
    // BottomLeft
    screen[H][0]=char(200); zone[H][0]=1;
    // BottomRight
    screen[H][W]=char(188); zone[H][W]=1;
}

// Safezone Border
void makeSafeBorder()
{
    // Top
    for (int x=0; x<W; x++) screen[0][x]=char(196);
    // Left
    for (int y=0; y<H; y++) screen[y][0]=char(179);
    // Bottom
    for (int x=0; x<W; x++) screen[H][x]=char(196);
    // Right
    for (int y=0; y<H; y++) screen[y][W]=char(179);
    // TopLeft
    screen[0][0]=char(218);
    // TopRight
    screen[0][W]=char(191);
    // BottomLeft
    screen[H][0]=char(192);
    // BottomRight
    screen[H][W]=char(217);
}
void safeBorderLogic()
{
    // Left side
    if (snakeX==W)
    {
        screen[snakeY][snakeX]=char(179);
        snakeX=1;
    }
    // Right side
    if (snakeX==0)
    {
        screen[snakeY][snakeX]=char(179);
        snakeX=W-1;
    }
    // Bot side
    if (snakeY==H)
    {
        screen[snakeY][snakeX]=char(196);
        snakeY=1;
    }
    // Top side
    if (snakeY==0)
    {
        screen[snakeY][snakeX]=char(196);
        snakeY=H-1;
    }

}



// 0 = safe
// 1 = dangerous
// 2 = food
// 3 = bigFood

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
    cout << "IU Snake ver 0.01beta";
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
    for (int i=0; i<=H; i++){
        gotoxy(scrX,scrY+i);
        for (int j=0; j<=W; j++) cout << screen[i][j];
    }
}


// getKey --> snakeMove
void getKey()
{
    char tempDir;

    if (_kbhit()) //Keyboard Hit
    {
        switch (_getch())
        {
        case 'A':
        case 'a':
        case KEY_LEFT:
            tempDir='L';
            break;
        case 'S':
        case 's':
        case KEY_DOWN:
            tempDir='D';
            break;
        case 'D':
        case 'd':
        case KEY_RIGHT:
            tempDir='R';
            break;
        case 'W':
        case 'w':
        case KEY_UP:
            tempDir='U';
            break;
        }
        gameStart=true;
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

    for (int i=0; i<numTails-1; i++) // Tail
    {
        screen[tailY[i]][tailX[i]]=char(snakeTailIcon);
        zone[tailY[i]][tailX[i]]=1;
    }
    screen[snakeY][snakeX]=char(snakeHeadIcon); //Head


}

void deleteSnake()
{
    screen[snakeY][snakeX]=' ';
}
// Food Spawn (Fail)
void foodSpawn()
{

    do
    {
        srand(time(NULL));
        foodX=rand()%W;
        foodY=rand()%H;
    }
    while (zone[foodY][foodX]!=0 || (foodX==snakeX && foodY==snakeY) || (foodX==0) || (foodY==0));

    screen[foodY][foodX]=char(foodIcon);
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

    if (zone[snakeY][snakeX]==1) gameOver=true;
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

        timer+=gameSpeed;


        Sleep(gameSpeed);
        infoBoard();
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

void mapSelect (){
}

void playScreen ()
{
    init();

    while (gameOver!=true)
        {
            draw();
            ShowConsoleCursor(false);
        }
}

void resultScreen (){
}

/*---------------MainFunc--------------------*/
int main()
{
    SetConsoleOutputCP(437);
    playScreen();
    system("pause");
    return 0;
}
