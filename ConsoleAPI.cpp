#ifndef CONSOLEAPI_H_INCLUDED
    #include "ConsoleAPI.h"
#endif // CONSOLEAPI_H_INCLUDED

#ifndef DECLARATION_H_INCLUDED
    #include "Declaration.h"
#endif // DECLARATION_H_INCLUDED

#include <windows.h>

using namespace std;

extern char ConsoleTitle[];

void goToXY(int x, int y)
{
    static HANDLE hi = NULL;
    if(!hi)
    hi = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(hi, c);
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
    SetTextColor(15);

    // Remove Cursor
    ShowConsoleCursor(false);
    /*GetConsoleCursorInfo(wHnd, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(wHnd, &cursorInfo);*/
    // Change Title

    SetConsoleTitle(TEXT(ConsoleTitle));

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
