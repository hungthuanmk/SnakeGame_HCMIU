#ifndef DECLARATION_H_INCLUDED
    #include "Declaration.h"
#endif // DECLARATION_H_INCLUDED

#ifndef GAMEPLAY_H_INCLUDED
    #include "GamePlay.h"
#endif // GAMEPLAY_H_INCLUDED

#ifndef CONSOLEAPI_H_INCLUDED
    #include "ConsoleAPI.h"
#endif // CONSOLEAPI_H_INCLUDED

#include "Screens.h"
#include <iostream>
#include <conio.h>

#include <windows.h>


using namespace std;

extern bool gameOver;

void mainMenu()
{


    ConsoleSetup();
    makeSafeBorder();
    drawScreen();

    int line=1, space=3;
    goToXY(scrX+space,scrY+(line++));
    cout << "  ______                       __                 ";

    goToXY(scrX+space,scrY+(line++));
    cout << " /      \\                     |  \\                ";

    goToXY(scrX+space,scrY+(line++));
    cout << "|  $$$$$$\\ _______    ______  | $$   __   ______  ";

    goToXY(scrX+space,scrY+(line++));
    cout << "| $$___\\$$|       \\  |      \\ | $$  /  \\ /      \\ ";

    goToXY(scrX+space,scrY+(line++));
    cout << " \\$$    \\ | $$$$$$$\\  \\$$$$$$\\| $$_/  $$|  $$$$$$\\";

    goToXY(scrX+space,scrY+(line++));
    cout << " _\\$$$$$$\\| $$  | $$ /      $$| $$   $$ | $$    $$";

    goToXY(scrX+space,scrY+(line++));
    cout << "|  \\__| $$| $$  | $$|  $$$$$$$| $$$$$$\\ | $$$$$$$$";

    goToXY(scrX+space,scrY+(line++));
    cout << " \\$$    $$| $$  | $$ \\$$    $$| $$  \\$$\\ \\$$     \\";

    goToXY(scrX+space,scrY+(line++));
    cout << "  \\$$$$$$  \\$$   \\$$  \\$$$$$$$ \\$$   \\$$  \\$$$$$$$";

    goToXY(scrX+space,scrY+(line++));
    cout << "";

    goToXY(scrX+space,scrY+(line++));
    cout << "";

    goToXY(scrX+space,scrY+(line++));
    cout << "";

    goToXY(scrX+space,scrY+(line++));
    cout << "                   START NEW GAME";

    goToXY(scrX+space,scrY+(line++));
    cout << "                     MAP SELECT";

    goToXY(scrX+space,scrY+(line++));
    cout << "                       ABOUT";

    goToXY(scrX+space,scrY+(line++));
    cout << "                     QUIT GAME :(";




    //selectMenu();

}

void playScreen ()
{
    init();
    while (gameOver!=true)
        draw();
}

void mapScreen()
{

}

void aboutScreen()
{

}

void resultScreen()
{

}

void selectMenu()
{
    char _key;
    int menuID = 1;
    while (_key != KEY_ENTER)
    {
        _key = _getch();
        if (_key == 0 || _key == 224)
        {
            goToXY(13, 10 + menuID);
            cout << "   ";
            _key = _getch();
            switch (_key)
            {
                case KEY_UP:
                    menuID--;
                    break;
                case KEY_DOWN:
                    menuID++;
                    break;
            }

            if (menuID > 4)
                menuID = 1;
            if (menuID < 1)
                menuID = 4;
            goToXY(13, 10 + menuID);
            cout << ">>>";
        }
    }
}


