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


void PrintMainMenu() {
    for (int i = 0; i < mapWidth; i++)
    {
        map[0][i] = '#';
        map[mapHeight - 1][i] = '#';
    }
    for (int j = 1; j < mapHeight - 1; j++)
    {
        map[j][0] = '#';
        map[j][mapWidth-1] = '#';
    }
    //буквым в менюшке
    map[3][20] = (char)219;
    map[4][20] = (char)219;
    map[5][20] = (char)219;
    map[7][20] = (char)219;
    map[9][20] = (char)219;
    map[10][20] = (char)219;
    map[11][20] = (char)219;
    map[12][20] = (char)219;
    map[13][20] = (char)219;

    map[3][21] = (char)219;
    map[4][21] = (char)219;
    map[5][21] = (char)219;
    map[7][21] = (char)219;
    map[10][21] = (char)219;

    map[3][22] = (char)219;
    map[5][22] = (char)219;
    map[7][22] = (char)219;
    map[11][22] = (char)219;

    map[3][23] = (char)219;
    map[5][23] = (char)219;
    map[6][23] = (char)219;
    map[7][23] = (char)219;
    map[10][23] = (char)219;

    map[3][24] = (char)219;
    map[5][24] = (char)219;
    map[6][24] = (char)219;
    map[7][24] = (char)219;
    map[9][24] = (char)219;
    map[10][24] = (char)219;
    map[11][24] = (char)219;
    map[12][24] = (char)219;
    map[13][24] = (char)219;

    map[3][26] = (char)219;
    map[4][26] = (char)219;
    map[5][26] = (char)219;
    map[6][26] = (char)219;
    map[10][26] = (char)219;
    map[11][26] = (char)219;
    map[12][26] = (char)219;
    map[13][26] = (char)219;

    map[7][27] = (char)219;
    map[9][27] = (char)219;
    map[11][27] = (char)219;

    map[7][28] = (char)219;
    map[9][28] = (char)219;
    map[11][28] = (char)219;

    map[7][29] = (char)219;
    map[9][29] = (char)219;
    map[11][29] = (char)219;

    map[3][30] = (char)219;
    map[4][30] = (char)219;
    map[5][30] = (char)219;
    map[6][30] = (char)219;
    map[10][30] = (char)219;
    map[11][30] = (char)219;
    map[12][30] = (char)219;
    map[13][30] = (char)219;

    map[3][32] = (char)219;
    map[4][32] = (char)219;
    map[5][32] = (char)219;
    map[6][32] = (char)219;
    map[7][32] = (char)219;
    map[9][32] = (char)219;
    map[10][32] = (char)219;
    map[11][32] = (char)219;
    map[12][32] = (char)219;
    map[13][32] = (char)219;

    map[3][33] = (char)219;
    map[5][33] = (char)219;
    map[9][33] = (char)219;
    map[11][33] = (char)219;

    map[3][34] = (char)219;
    map[5][34] = (char)219;
    map[9][34] = (char)219;
    map[11][34] = (char)219;
    map[12][34] = (char)219;

    map[4][35] = (char)219;
    map[10][35] = (char)219;
    map[12][35] = (char)219;
    map[13][35] = (char)219;

    map[3][37] = (char)219;
    map[4][37] = (char)219;
    map[5][37] = (char)219;
    map[6][37] = (char)219;
    map[7][37] = (char)219;
    map[9][37] = (char)219;
    map[13][37] = (char)219;

    map[3][38] = (char)219;
    map[5][38] = (char)219;
    map[7][38] = (char)219;
    map[9][38] = (char)219;
    map[10][38] = (char)219;
    map[11][38] = (char)219;
    map[12][38] = (char)219;
    map[13][38] = (char)219;

    map[3][39] = (char)219;
    map[5][39] = (char)219;
    map[7][39] = (char)219;
    map[9][39] = (char)219;
    map[13][39] = (char)219;

    map[3][41] = (char)219;
    map[4][41] = (char)219;
    map[5][41] = (char)219;
    map[6][41] = (char)219;
    map[7][41] = (char)219;
    map[10][41] = (char)219;
    map[11][41] = (char)219;
    map[12][41] = (char)219;

    map[3][42] = (char)219;
    map[5][42] = (char)219;
    map[9][42] = (char)219;
    map[13][42] = (char)219;

    map[3][43] = (char)219;
    map[5][43] = (char)219;
    map[6][43] = (char)219;
    map[9][43] = (char)219;
    map[13][43] = (char)219;

    map[4][44] = (char)219;
    map[6][44] = (char)219;
    map[7][44] = (char)219;
    map[10][44] = (char)219;
    map[11][44] = (char)219;
    map[12][44] = (char)219;

    map[17][21] = 'P';
    map[17][22] = 'r';
    map[17][23] = 'e';
    map[17][24] = 's';
    map[17][25] = 's';
    map[17][26] = ' ';
    map[17][27] = '"';
    map[17][28] = 'S';
    map[17][29] = 'p';
    map[17][30] = 'a';
    map[17][31] = 'c';
    map[17][32] = 'e';
    map[17][33] = '"';
    map[17][34] = ' ';
    map[17][35] = 't';
    map[17][36] = 'o';
    map[17][37] = ' ';
    map[17][38] = 's';
    map[17][39] = 't';
    map[17][40] = 'a';
    map[17][41] = 'r';
    map[17][42] = 't';

    map[19][21] = 'P';
    map[19][22] = 'r';
    map[19][23] = 'e';
    map[19][24] = 's';
    map[19][25] = 's';
    map[19][26] = ' ';
    map[19][27] = '"';
    map[19][28] = 'E';
    map[19][29] = 'S';
    map[19][30] = 'C';
    map[19][31] = '"';
    map[19][32] = ' ';
    map[19][33] = 't';
    map[19][34] = 'o';
    map[19][35] = ' ';
    map[19][36] = 'e';
    map[19][37] = 'x';
    map[19][38] = 'i';
    map[19][39] = 't';

    PrintMap();
    system("Pause");
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