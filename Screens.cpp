#include "Screens.h"
#ifndef GAMEPLAY_H_INCLUDED
    #include "GamePlay.h"
#endif // GAMEPLAY_H_INCLUDED

using namespace std;

extern bool gameOver;

void mainMenu()
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

void mapScreen()
{

}

void aboutScreen()
{

}

void resultScreen()
{

}


