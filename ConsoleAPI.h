#ifndef CONSOLEAPI_H_INCLUDED
#define CONSOLEAPI_H_INCLUDED

/**
    Move cursor to position (X,Y).
    @param x X
    @param y Y
*/
void goToXY(int x, int y);

/**
    Set cursor visibility.
    @param showFlag show=true (hide=false)
*/
void ShowConsoleCursor(bool showFlag);

/**
    Change text color.
    @param ForgC COlOR - see more at "Declaration.h"
*/
void SetTextColor(int ForgC);

/**
    Setup console environment for game.
    -> Move windows
    -> Hide cursor
    -> Change windows title
    -> Change codepage
    -> Set font and color
*/
void ConsoleSetup();

#endif // CONSOLEAPI_H_INCLUDED
