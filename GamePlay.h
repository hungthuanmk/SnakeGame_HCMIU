#ifndef GAMEPLAY_H_INCLUDED
#define GAMEPLAY_H_INCLUDED

void makeDangerBorder();
// Safezone Border
void makeSafeBorder();
void safeBorderLogic();
// 0 = safe
// 1 = dangerous

// Setup process
void init();
/*---------------BackEnd--------------------*/
void infoBoard ();
void debug();
void drawScreen();
// getKey --> snakeMove
void getKey();
void snakeMove();
void makeSnake();
void deleteSnake();
// Food Spawn (Fail)
void foodSpawn();
// Tail
void saveTail();
// Game Logical
void logic();
// This draw
void draw();

#endif // GAMEPLAY_H_INCLUDED
