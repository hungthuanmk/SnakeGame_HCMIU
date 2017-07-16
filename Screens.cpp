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

using namespace std;

extern bool gameOver;

void mainMenu()
{
    ConsoleSetup();
    cout << "  ______                       __                 \n";
    cout << " /      \\                     |  \\                \n";
    cout << "|  $$$$$$\\ _______    ______  | $$   __   ______  \n";
    cout << "| $$___\\$$|       \\  |      \\ | $$  /  \\ /      \\ \n";
    cout << " \\$$    \\ | $$$$$$$\\  \\$$$$$$\\| $$_/  $$|  $$$$$$\\\n";
    cout << " _\\$$$$$$\\| $$  | $$ /      $$| $$   $$ | $$    $$\n";
    cout << "|  \\__| $$| $$  | $$|  $$$$$$$| $$$$$$\\ | $$$$$$$$\n";
    cout << " \\$$    $$| $$  | $$ \\$$    $$| $$  \\$$\\ \\$$     \\\n";
    cout << "  \\$$$$$$  \\$$   \\$$  \\$$$$$$$ \\$$   \\$$  \\$$$$$$$";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "                   START NEW GAME\n";
    cout << "                     MAP SELECT\n";
    cout << "                       ABOUT\n";
    cout << "                     QUIT GAME :(\n";
    selectMenu();
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


