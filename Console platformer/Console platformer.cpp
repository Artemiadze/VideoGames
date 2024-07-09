#include <Windows.h>
#include "Map.h"



int main()
{
    ClearMap();
    system("mode con cols=80 lines=26");
    PrintMainMenu();
    if (GetKeyState(VK_SPACE) < 0) {
        CreateLevel(level);
        system("mode con cols=80 lines=26");
        do {
            if (GetKeyState('E') < 0) {
                system("Pause");
            }
            ClearMap();

            if ((Mario.isFly == FALSE) && (GetKeyState(VK_SPACE) < 0)) {
                Mario.vertSpeed = -1;
            }
            if (GetKeyState('D') < 0) {
                HorizonMapMove(-1);
            }
            if (GetKeyState('A') < 0) {
                HorizonMapMove(1);
            }

            if (Mario.y > mapHeight) {
                PlayerDead(level);
            }

            VertMoveSpeed(&Mario);
            MarioCollision();

            for (int i = 0; i < brickLenght; i++) {
                PutObjectOnMap(brick[i]);
            }
            for (int i = 0; i < Moving_block_Length; i++) {
                VertMoveSpeed(moving_block + i);
                HorizonMoveObject(moving_block + i);
                PutObjectOnMap(moving_block[i]);

                if (moving_block[i].y > mapHeight)
                {
                    {
                        DeleteMovingBlock(i);
                        i--;
                        continue;
                    }
                }
            }
            PutObjectOnMap(Mario);
            PrintScore();

            SetCur(0, 0);
            PrintMap();

            Sleep(10);
        } while (GetKeyState(VK_ESCAPE) >= 0);
    }
    else {
        exit(1);
    }
    

    return 0;
}
