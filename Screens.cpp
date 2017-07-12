#include "Screens.h"
#ifndef GAMEPLAY_H_INCLUDED
    #include "GamePlay.h"
#endif // GAMEPLAY_H_INCLUDED
#ifndef CONSOLEAPI_H_INCLUDED
    #include "ConsoleAPI.h"
#endif // CONSOLEAPI_H_INCLUDED
#include <iostream>

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
    //goToXY(13, 11);
    //cout << " >>> ";
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
 //   char _key;
 //  while ()
}


