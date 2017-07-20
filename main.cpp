#include <iostream>
#include <conio.h>
#include "Screens.h"
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib,"libwinmm.a")

using namespace std;

char ConsoleTitle[] = "IU Snake 0.4*** Updated: 20/07/2017";
char version[] = "0.4";



int main()
{

    PlaySound(TEXT("soundtrack\\StartScreen.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    mainMenu();
    getch();
    system("cls");
    PlaySound(NULL, 0, 0);


    playScreen();
    getch();
    return 0;
}
