#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED

/**
    Make danger border.
*/
void makeDangerBorder();

/**
    Make danger border.
*/
void makeSafeBorder();

/**
    Safe border logical movement.
*/
void safeBorderLogic();

/**
    Init gameplay.
    -> ConsoleSetup() see more "ConsoleAPI.h"
*/
void init();
/*---------------BackEnd--------------------*/
/**
    Show score board.
*/
void infoBoard ();

/**
    Show debug screen.
*/
void debug();

/**
    Draw all character in array screen[][].
*/
void drawScreen();

/**
    Get key input and change snake's direction.
*/
void getKey();

/**
    Move snake's head and tails.
*/
void snakeMove();

/**
    Print snakes icon into array screen[][] and set zone[][].
*/
void makeSnake();

/**
    Clear old snake's icon in screen[][].
*/
void deleteSnake();

/**
    Spawn new food.
*/
void foodSpawn();

/**
    Create snake's tail in screen[][] and zone[][].
*/
void saveTail();

/**
    Gameplay logical ex: hit tail, hit border...
*/
void logic();

/**
    Run all need steps in each of game frames.
*/
void draw();

#endif // GAMEPLAY_H_INCLUDED
