#include <iostream>
#include <conio.h>
#include "Screens.h"
#include <windows.h>

using namespace std;

char ConsoleTitle[] = "IU Snake - By Xuan Tung and HTML *** Updated: 16/07/2017";
char version[] = "0.4";

int main()
{
    mainMenu();
    getch();
    system("cls");
    playScreen();
    getch();
    return 0;
}
