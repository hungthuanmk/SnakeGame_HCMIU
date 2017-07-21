#ifndef DECLARATION_H_INCLUDED
#define DECLARATION_H_INCLUDED

// CONSTANTS

#define Debug   false

#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_LEFT    75
#define KEY_RIGHT   77
#define KEY_ENTER   13

#define foodIcon         254
#define snakeHeadIcon    178
#define snakeTailIcon    176
#define SCREEN_LEFT      179
#define SCREEN_RIGHT     179
#define SCREEN_BOTTOM    196
#define SCREEN_TOP       196
#define SCREEN_TOP_LEFT  218
#define SCREEN_TOP_RIGHT 191
#define SCREEN_BOT_LEFT  192
#define SCREEN_BOT_RIGHT 217

#define defaultColor     15
#define snakeHeadColor   2
#define snakeTailColor   14

#define MAX_TAIL (W-2)*(H-2)

const int W = 55;   //Screen Width
const int H = 20;   //Screen Height

const int scrX = 3;    //Screen LeftTop X
const int scrY = 2;    //Screen LeftTop Y


///      COLOR             | VALUE
 #define COLOR_BLACK           0
 #define COLOR_BLUE            1
 #define COLOR_GREEN           2
 #define COLOR_CYAN            3
 #define COLOR_RED             4
 #define COLOR_MAGENTA         5
 #define COLOR_BORWN           6
 #define COLOR_lGRAY           7
 #define COLOR_dGRAY           8
 #define COLOR_lBLUE           9
 #define COLOR_lGREEN          10
 #define COLOR_lCYAN           11
 #define COLOR_lRED            12
 #define COLOR_lMAGENTA        13
 #define COLOR_YELLOW          14
 #define COLOR_WHITE           15
//////////////////////////////////

///      SOUND      | FILENAME
 #define SOUND_MENU "soundtrack\\StartScreen.wav"
/////////////////////////////////

#endif // DECLARATION_H_INCLUDED
