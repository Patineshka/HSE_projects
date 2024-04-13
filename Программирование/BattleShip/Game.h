#pragma once

#define N_LINSE 13
#define FIELD_SIZE 19
#define PLAYER_1 0
#define PLAYER_2 ~PLAYER_1 //ИГРОК 2 ЭТО НЕ ВЕРСИЯ ИГРОКА 1
#define BoT 2 //бот

#define ARROW_KEY_PRESSED 0xE0
#define KEY_ENTER 13
#define FIRE 32
#define KEY_UP 72
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_LEFT 75
#define TARGET '+'


typedef struct BOAT{
    int numberOfDescks;
    int coordinates[4][2];
    int numberOfHits;
    int regulation; //1 - горизонтально, 2 - вертикально
}BOAT;


typedef enum
{
    DEC1 = 0
    , DEC2
    , EX

}CONDITION;

typedef enum
{
    INIT1 = 0
    , DRAW1
    , INIT2
    , DRAW2
    , DRAW
    , WAITING
    , PROCESSING
    , CHECK
    , EXIT

}eGameState;
//----------------------------------------------------------------
typedef enum
{
    EMPTY = 0
    , SHOT
    , STRIKE
    , KILL
    , SHIP
    , SHELL
    , EFIELD_INFO_END
}eFieldInfo;
//----------------------------------------------------------------

void draw_field(eFieldInfo* ap_data, eFieldInfo* ap_dataP, unsigned short a_target, int tmp, char* opponentName);
void ship_generate(eFieldInfo* ap_data, struct BOAT* boat);
unsigned char get_target_possition(unsigned char* ap_x, unsigned char* ap_y);
unsigned char shot_analiz(eFieldInfo* ap_dataP, eFieldInfo* ap_data, int x, int y, int* score, int tmp1);
unsigned char shotBOT_analiz(eFieldInfo* ap_data, int x, int y, int* score, int tmp1);
void analiz(eFieldInfo* ap_dataP1, eFieldInfo* ap_data1, int x, int y, struct BOAT* boat);
unsigned short BOT(int* sea, eFieldInfo* ap_data, int m, int a, int b);