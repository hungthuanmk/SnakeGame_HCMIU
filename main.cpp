#include <iostream>
#include <conio.h>
#include "Screens.h"

using namespace std;

char ConsoleTitle[] = "IU Snake - By Xuan Tung and HTML *** Updated: 12/07/2017";
char version[] = "0.4";

int main()
{
    mainMenu();
    getch();
    playScreen();
    return 0;
}
