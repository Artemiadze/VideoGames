#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <Windows.h>
#include "Map.h"

//ширина и высота
#define mapWidth 80
#define mapHeight 25 

typedef struct Object TObject;
char map[mapHeight][mapWidth + 1];
TObject Mario; //Марио 
//массив brick динамический 
TObject* brick = NULL; // блоки - сделаем массивом чтобы потом было просто добавлять обьекты
TObject* moving_block = NULL; //блоки с монетками

int Moving_block_Length;
int brickLenght;
int level = 1;
int score;


//создаёт карту
void ClearMap() {
    for (int i = 0; i < mapWidth; i++)
    {
        map[0][i] = ' ';
    }
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j++)
    {
        //присваивает для map[j] значение из map[0]
        sprintf(map[j], map[0]);
    }
}

//печатает карту
void PrintMap() {
    map[mapHeight - 1][mapWidth] = '\0';
    for (int i = 0; i < mapHeight; i++) {
        printf("%s\n", map[i]);
    }
}


//Задаёт позицию персонажа
void SetObjectPos(TObject* obj, float xPos, float yPos) {
    //меняем значение входной переменной obj, поэтому используем указатель
    obj->x = xPos;
    obj->y = yPos;
}


void SetCur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    //GetStdHandle - возвращает адрес определяемый входным параметром (Стандартного устр. вывода (STD_OUTPUT_HANDLE))
    //SetConsoleCursorPosition - получает адрес консоли и устанавливает место курсора
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


//не вышли мы за предел границы
BOOL IsPositionMap(int x, int y) {
    return ((x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight));
}


//столкновение с поверхностью
BOOL IsCollision(TObject T1, TObject T2) {
    return ((T1.x + T1.width) > T2.x) && (T1.x < (T2.x + T2.width)) && ((T1.y + T1.height) > T2.y) && (T1.y < (T2.y + T2.height));
}


TObject* getNewBrick() {
    brickLenght++;
    brick = (TObject*)realloc(brick, sizeof(*brick) * brickLenght);
    return brick + brickLenght - 1; //функция вернёт указатель на элемент массива
}


TObject* getNewMoving() {
    Moving_block_Length++;
    moving_block = (TObject*)realloc(moving_block, sizeof(*moving_block) * Moving_block_Length);
    return moving_block + Moving_block_Length - 1; //функция вернёт указатель на элемент массива
}

void CreateLevel(int lvl);


//инициализирует данные обьекта
//change . to ->
void InitObject(TObject* obj, float xPos, float yPos, float oWidth, float oHeight, char oType) {
    SetObjectPos(obj, xPos, yPos);
    (*obj).width = oWidth; //obj->width
    (*obj).height = oHeight;
    (*obj).vertSpeed = 0;
    (*obj).cType = oType;
    (*obj).HorizionSpeed = 0.2;
}


void PlayerDead(int level)
{
    system("color 4F");
    Sleep(500);
    CreateLevel(level);
}


//меняет скорость
void VertMoveSpeed(TObject* obj) {
    obj->isFly = TRUE;
    obj->vertSpeed += 0.05;
    SetObjectPos(obj, obj->x, obj->y + obj->vertSpeed);

    for (int i = 0; i < brickLenght; i++) {
        if (IsCollision(*obj, brick[i])) //если столкнулся с землей то стоит на месте
        {

            if (obj->vertSpeed > 0)
            {
                obj->isFly = FALSE;
            }

            if ((brick[i].cType == '?') && (obj->vertSpeed < 0) && (obj == &Mario))
            {
                brick[i].cType = '-';
                InitObject(getNewMoving(), brick[i].x, brick[i].y - 3, 3, 2, '$');
                moving_block[Moving_block_Length - 1].vertSpeed = -0.7; //зададим отрицательную скорость чтобы деньги подпрыгивали
            }

            obj->y -= obj->vertSpeed;
            obj->vertSpeed = 0;
            if (brick[i].cType == (char)177) {
                level++;
                if (level > 3) level = 1;//если прошли все уровни то возвращаем всё к началу
                system("color 2F");
                Sleep(500);
                CreateLevel(level);
            }
            break;
        }
    }
}


//функция перемещения карты по экрану
void HorizonMapMove(float dx) {
    Mario.x -= dx;
    for (int i = 0; i < brickLenght; i++) {
        if (IsCollision(Mario, brick[i])) {
            Mario.x += dx;
            return;
        }
    }
    Mario.x += dx;

    //теперь обьекты будут перемещаться вместе с картой и скрываться
    //если они оказались за картой 
    for (int i = 0; i < brickLenght; i++)
        brick[i].x += dx;
    for (int i = 0; i < Moving_block_Length; i++)
        moving_block[i].x += dx;
}



//удаление мобов при прыжке на них
void DeleteMovingBlock(int i)
{
    Moving_block_Length--;
    moving_block[i] = moving_block[Moving_block_Length];
    moving_block = (TObject*)realloc(moving_block, sizeof(*moving_block) * Moving_block_Length);
}


//проверка Марио на взаимодействие с обьектами
void MarioCollision()
{
    for (int i = 0; i < Moving_block_Length; i++)
    {
        if (IsCollision(Mario, moving_block[i]))
        {
            if (moving_block[i].cType == 'o')
            {
                //мы выше и летим вниз и наши ноги выше головы врага
                if (Mario.isFly == TRUE && Mario.vertSpeed > 0 && Mario.y + Mario.height < moving_block[i].y + moving_block[i].height * 0.5)
                {
                    score += 50;
                    DeleteMovingBlock(i);
                    i--;
                    continue;
                }
                else {
                    PlayerDead(level);
                }
            }
            if (moving_block[i].cType == '$')
            {
                score += 100;
                DeleteMovingBlock(i);
                i--;
                continue;
            }
        }
    }
}


//процедура горизонтального перемещения обьектов
//ИИ для ботов
void HorizonMoveObject(TObject* obj) {
    obj->x += obj->HorizionSpeed;
    for (int i = 0; i < brickLenght; i++)
    {
        if (IsCollision(obj[0], brick[i]))
        {
            obj->x -= obj->HorizionSpeed;
            obj->HorizionSpeed = -(obj->HorizionSpeed);
            return;
        }
    }

    //если враг то он не будет падать с кирпичиков
    //а все остальные будут
    if (obj->cType == 'o')
    {
        //если он упадёт то он пойдет обратно
        TObject tmp = *obj;
        VertMoveSpeed(&tmp);
        if (tmp.isFly == TRUE) {
            obj[0].x -= obj[0].HorizionSpeed;
            obj[0].HorizionSpeed = -obj[0].HorizionSpeed;
            return;
        }
    }
}


void PutObjectOnMap(TObject obj) {
    int ix = (int)round(obj.x); //static_cast<int>(obj.x)
    int iy = (int)round(obj.y); //static_cast<int>(obj.y)
    int iWidth = (int)round(obj.width);
    int iHeight = (int)round(obj.height);

    for (int i = ix; i < (ix + iWidth); i++) {
        for (int j = iy; j < (iy + iHeight); j++) {
            if (IsPositionMap(i, j))
                map[j][i] = obj.cType;
        }
    }
}


void PrintScore() {
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);
    for (int i = 0; i < len; i++)
    {
        map[1][i + 5] = c[i];
    }
}


void CreateLevel(int lvl) {

    system("color 9F");

    brickLenght = 0;
    Moving_block_Length = 0;
    brick = (TObject*)realloc(brick, 0);
    moving_block = (TObject*)realloc(moving_block, 0);
    score = 0;

    InitObject(&Mario, 39, 10, 3, 3, '@');

    if (level == 1) {
        InitObject(getNewBrick(), 20, 20, 40, 5, (char)219);
        InitObject(getNewBrick(), 60, 15, 10, 10, (char)219);
        InitObject(getNewBrick(), 80, 20, 20, 10, (char)219);
        InitObject(getNewBrick(), 120, 15, 10, 10, (char)219);
        InitObject(getNewBrick(), 150, 20, 40, 5, (char)219);
        InitObject(getNewBrick(), 200, 20, 40, 5, (char)219);
        // замок (блок успешного прохождения уровня)
        InitObject(getNewBrick(), 230, 15, 10, 5, (char)177); //+20
        InitObject(getNewBrick(), 230, 14, 1, 1, (char)177);
        InitObject(getNewBrick(), 239, 14, 1, 1, (char)177);
        InitObject(getNewBrick(), 234, 16, 2, 4, '-');
        InitObject(getNewBrick(), 232, 11, 6, 4, (char)177);
        InitObject(getNewBrick(), 232, 10, 1, 1, (char)177);
        InitObject(getNewBrick(), 234, 10, 2, 1, (char)177);
        InitObject(getNewBrick(), 237, 10, 1, 1, (char)177);
        InitObject(getNewBrick(), 233, 12, 1, 2, '-');
        InitObject(getNewBrick(), 236, 12, 1, 2, '-');

        InitObject(getNewMoving(), 25, 10, 2, 2, 'o');
        InitObject(getNewMoving(), 65, 10, 2, 2, 'o');
        InitObject(getNewMoving(), 120, 10, 2, 2, 'o');
        InitObject(getNewMoving(), 175, 10, 2, 2, 'o');
    }
    if (level == 2) {
        InitObject(getNewBrick(), 20, 20, 40, 5, (char)219);

        InitObject(getNewBrick(), 30, 10, 5, 3, '?');
        InitObject(getNewBrick(), 50, 10, 5, 3, '?');

        InitObject(getNewBrick(), 60, 5, 10, 3, '-');
        InitObject(getNewBrick(), 70, 5, 5, 3, '?');
        InitObject(getNewBrick(), 75, 5, 5, 3, '-');
        InitObject(getNewBrick(), 80, 5, 5, 3, '?');
        InitObject(getNewBrick(), 85, 5, 10, 3, '-');

        InitObject(getNewMoving(), 125, 5, 2, 2, 'o');
        InitObject(getNewMoving(), 155, 10, 2, 2, 'o');

        InitObject(getNewBrick(), 60, 15, 40, 10, (char)219);
        InitObject(getNewBrick(), 100, 20, 20, 10, (char)219);
        InitObject(getNewBrick(), 120, 15, 10, 10, (char)219);
        InitObject(getNewBrick(), 150, 20, 40, 5, (char)219);

        InitObject(getNewBrick(), 210, 20, 40, 5, (char)219);
        // замок (блок успешного прохождения уровня)
        InitObject(getNewBrick(), 230, 15, 10, 5, (char)177);
        InitObject(getNewBrick(), 230, 14, 1, 1, (char)177);
        InitObject(getNewBrick(), 239, 14, 1, 1, (char)177);
        InitObject(getNewBrick(), 234, 16, 2, 4, '-');
        InitObject(getNewBrick(), 232, 11, 6, 4, (char)177);
        InitObject(getNewBrick(), 232, 10, 1, 1, (char)177);
        InitObject(getNewBrick(), 234, 10, 2, 1, (char)177);
        InitObject(getNewBrick(), 237, 10, 1, 1, (char)177);
        InitObject(getNewBrick(), 233, 12, 1, 2, '-');
        InitObject(getNewBrick(), 236, 12, 1, 2, '-');

        InitObject(getNewMoving(), 25, 10, 2, 2, 'o');
        InitObject(getNewMoving(), 80, 10, 2, 2, 'o');
        InitObject(getNewMoving(), 105, 10, 2, 2, 'o');
    }
    if (level == 3) {
        InitObject(getNewBrick(), 0, 21, 207, 4, (char)219);

        InitObject(getNewBrick(), 48, 13, 3, 2, '?');
        InitObject(getNewBrick(), 60, 13, 3, 2, (char)219);
        InitObject(getNewBrick(), 63, 13, 3, 2, '?');
        InitObject(getNewBrick(), 66, 13, 3, 2, (char)219);
        InitObject(getNewBrick(), 69, 13, 3, 2, '?');
        InitObject(getNewBrick(), 72, 13, 3, 2, (char)219);
        InitObject(getNewBrick(), 66, 5, 3, 2, '?');

        InitObject(getNewBrick(), 84, 17, 6, 2, (char)219);
        InitObject(getNewBrick(), 85, 19, 4, 2, (char)219);

        InitObject(getNewBrick(), 114, 15, 6, 2, (char)219);
        InitObject(getNewBrick(), 115, 17, 4, 4, (char)219);

        InitObject(getNewBrick(), 138, 13, 6, 2, (char)219);
        InitObject(getNewBrick(), 139, 15, 4, 6, (char)219);

        InitObject(getNewBrick(), 171, 13, 6, 2, (char)219);
        InitObject(getNewBrick(), 172, 15, 4, 6, (char)219);
        // --
        InitObject(getNewBrick(), 213, 21, 45, 4, (char)219);
        InitObject(getNewBrick(), 231, 13, 3, 2, (char)219);
        InitObject(getNewBrick(), 234, 13, 3, 2, '?');
        InitObject(getNewBrick(), 237, 13, 3, 2, (char)219);
        InitObject(getNewBrick(), 240, 5, 24, 2, (char)219);
        // --
        InitObject(getNewBrick(), 267, 21, 192, 4, (char)219);
        InitObject(getNewBrick(), 273, 5, 9, 2, (char)219);
        InitObject(getNewBrick(), 282, 5, 3, 2, '?');
        InitObject(getNewBrick(), 282, 13, 3, 2, '?');
        InitObject(getNewBrick(), 300, 13, 6, 2, (char)219);
        InitObject(getNewBrick(), 318, 13, 3, 2, '?');
        InitObject(getNewBrick(), 327, 13, 3, 2, '?');
        InitObject(getNewBrick(), 327, 5, 3, 2, '?');
        InitObject(getNewBrick(), 336, 13, 3, 2, '?');
        InitObject(getNewBrick(), 354, 13, 3, 2, (char)219);
        InitObject(getNewBrick(), 363, 5, 9, 2, (char)219);
        InitObject(getNewBrick(), 384, 5, 3, 2, (char)219);
        InitObject(getNewBrick(), 387, 5, 3, 2, '?');
        InitObject(getNewBrick(), 390, 5, 3, 2, '?');
        InitObject(getNewBrick(), 393, 5, 3, 2, (char)219);
        InitObject(getNewBrick(), 387, 13, 6, 2, (char)219);
        //лестница
        InitObject(getNewBrick(), 402, 19, 12, 2, (char)219);
        InitObject(getNewBrick(), 405, 17, 9, 2, (char)219);
        InitObject(getNewBrick(), 408, 15, 6, 2, (char)219);
        InitObject(getNewBrick(), 411, 13, 3, 2, (char)219);

        InitObject(getNewBrick(), 420, 13, 3, 2, (char)219);
        InitObject(getNewBrick(), 420, 15, 6, 2, (char)219);
        InitObject(getNewBrick(), 420, 17, 9, 2, (char)219);
        InitObject(getNewBrick(), 420, 19, 12, 2, (char)219);

        InitObject(getNewBrick(), 444, 19, 15, 2, (char)219);
        InitObject(getNewBrick(), 447, 17, 12, 2, (char)219);
        InitObject(getNewBrick(), 450, 15, 9, 2, (char)219);
        InitObject(getNewBrick(), 453, 13, 6, 2, (char)219);
        // --
        InitObject(getNewBrick(), 465, 21, 165, 4, (char)219);
        InitObject(getNewBrick(), 465, 13, 3, 2, (char)219);
        InitObject(getNewBrick(), 465, 15, 6, 2, (char)219);
        InitObject(getNewBrick(), 465, 17, 9, 2, (char)219);
        InitObject(getNewBrick(), 465, 19, 12, 2, (char)219);

        InitObject(getNewBrick(), 489, 17, 6, 2, (char)219);
        InitObject(getNewBrick(), 490, 19, 4, 2, (char)219);

        InitObject(getNewBrick(), 504, 13, 6, 2, (char)219);
        InitObject(getNewBrick(), 510, 13, 3, 2, '?');
        InitObject(getNewBrick(), 513, 13, 3, 2, (char)219);

        InitObject(getNewBrick(), 537, 17, 6, 2, (char)219);
        InitObject(getNewBrick(), 538, 19, 4, 2, (char)219);
        // лестница большая
        InitObject(getNewBrick(), 543, 19, 27, 2, (char)219);
        InitObject(getNewBrick(), 546, 17, 24, 2, (char)219);
        InitObject(getNewBrick(), 549, 15, 21, 2, (char)219);
        InitObject(getNewBrick(), 552, 13, 18, 2, (char)219);
        InitObject(getNewBrick(), 555, 11, 15, 2, (char)219);
        InitObject(getNewBrick(), 558, 9, 12, 2, (char)219);
        InitObject(getNewBrick(), 561, 7, 9, 2, (char)219);
        InitObject(getNewBrick(), 564, 5, 6, 2, (char)219);

        // замок
        InitObject(getNewBrick(), 600, 16, 10, 5, (char)177);
        InitObject(getNewBrick(), 600, 15, 1, 1, (char)177);
        InitObject(getNewBrick(), 609, 15, 1, 1, (char)177);
        InitObject(getNewBrick(), 604, 17, 2, 4, '-');
        InitObject(getNewBrick(), 602, 12, 6, 4, (char)177);
        InitObject(getNewBrick(), 602, 11, 1, 1, (char)177);
        InitObject(getNewBrick(), 604, 11, 2, 1, (char)177);
        InitObject(getNewBrick(), 607, 11, 1, 1, (char)177);
        InitObject(getNewBrick(), 603, 13, 1, 2, '-');
        InitObject(getNewBrick(), 606, 13, 1, 2, '-');

        InitObject(getNewMoving(), 66, 16, 2, 2, 'o');
        InitObject(getNewMoving(), 121, 16, 2, 2, 'o');
        InitObject(getNewMoving(), 153, 16, 2, 2, 'o');
        InitObject(getNewMoving(), 159, 16, 2, 2, 'o');

        InitObject(getNewMoving(), 238, 1, 2, 2, 'o');
        InitObject(getNewMoving(), 246, 1, 2, 2, 'o');
        InitObject(getNewMoving(), 321, 16, 2, 2, 'o');
        InitObject(getNewMoving(), 342, 16, 2, 2, 'o');
        InitObject(getNewMoving(), 348, 16, 2, 2, 'o');
        InitObject(getNewMoving(), 370, 16, 2, 2, 'o');
        InitObject(getNewMoving(), 391, 16, 2, 2, 'o');

        InitObject(getNewMoving(), 522, 16, 2, 2, 'o');
        InitObject(getNewMoving(), 526, 16, 2, 2, 'o');
    }
}