#ifndef MAP_H
#define MAP_H

#define mapWidth 80
#define mapHeight 25 


typedef struct Object {
    float x, y;
    float width, height;
    float vertSpeed;
    BOOL isFly; //в прыжке ли предмет 
    char cType;
    float HorizionSpeed;  //скорость по горизонтали
}TObject;

extern char map[mapHeight][mapWidth + 1];
extern TObject Mario;
extern TObject* brick;
extern TObject* moving_block;

extern int Moving_block_Length;
extern int brickLenght;
extern int level;
extern int score;

void ClearMap();
void PrintMap();
void SetCur(int x, int y);
void SetObjectPos(TObject* obj, float xPos, float yPos);

BOOL IsCollision(TObject T1, TObject T2);
BOOL IsPositionMap(int x, int y);
TObject* getNewMoving();
TObject* getNewBrick();
void CreateLevel(int lvl);
void InitObject(TObject* obj, float xPos, float yPos, float oWidth, float oHeight, char oType);
void PlayerDead(int level);
void VertMoveSpeed(TObject* obj);
void HorizonMapMove(float dx);
void DeleteMovingBlock(int i);
void MarioCollision();
void HorizonMoveObject(TObject* obj);
void PutObjectOnMap(TObject obj);
void PrintScore();
#endif