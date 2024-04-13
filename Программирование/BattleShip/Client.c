#include "Game.h"

#pragma comment(lib, "ws2_32.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <winsock.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>

void SendData2Server()
{
    SOCKET client;
    sockaddr_in localaddr;
    client = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (client == INVALID_SOCKET)
    {
        printf("Error create socket\n");
        return;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(2097); //the same as in server
    server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //special look-up address
    if (connect(client, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Can't connect to server\n");
        closesocket(client);
        return;
    }
    char message[1024];
    int ret;

    printf("Enter the name:\n");

    char name[20] = {0};
    gets_s(name);
    send(client, name, strlen(name), 0);

    int step;
    recv(client, message, sizeof(message), 0);
    step = message[0] - '0';

    printf("1 - play with bot\n2 - play with player\n");

    struct BOAT ship[10] = {0};
    char chose[3] = { 0 };
    gets_s(chose);
    send(client, chose, strlen(chose), 0);
    char opponentName[50];
    CONDITION clientChoise = ((strcmp(chose, "2") == 0)) ? DEC2 : DEC1;

    eGameState game_state = INIT1;
    unsigned char isRun = 1;
    int player = PLAYER_1;
    int tmp1 = 0;
    int score[2] = { 0, 0 };

    eFieldInfo p_data[10 * 10] = { EMPTY };
    eFieldInfo p_dataP[10 * 10] = { EMPTY };

    unsigned short shot_position = 0;
    unsigned short shot_position1 = 0;//для бота

    unsigned char target_x = 0;
    unsigned char target_y = 0;
    int s = 0; //счётчик попаданий для бота
    int m = 0; //ПЕРЕДАЁМ В ФУНКЦИЯ для бота
    int a = 0;//ДЛЯ БОТА
    int b = 0;//ДЛЯ БОТА
    char BotName[4] = "Bot";
    int sea[100] = { 0 }; //интовый массив для отслеживания попаданий бота  ПЕРЕДАЁМ В ФУНКЦИЮ
    eFieldInfo bot_data[10 * 10] = { EMPTY };
    while (isRun)
    {
        switch (clientChoise)
        {
        case DEC1:
        {
            switch (game_state)
            {
            case INIT1:
            {
                ship_generate(p_data, ship);//порядок действий по инициализации игры ИГРОКА№1
                game_state = DRAW1;
                break;
            }
            case DRAW1:
            {
                system("cls");//отчистка экрана
                //отрисовка и ввод данных
                draw_field(p_data, p_dataP, shot_position, 0, BotName);
                printf("Are you satisfied with the arrangement?\n");
                printf("press the space bar if you want to change the location of the ships / press enter to continue");
                switch (_getch())
                {
                case KEY_ENTER:
                {
                    ship_generate(bot_data, ship);//делаем карабли на поле бота
                    game_state = DRAW;
                    break;
                }
                case FIRE:
                {
                    game_state = INIT1;
                    break;
                }
                }
                break;

            }
            case DRAW:
            {
                system("cls");//отчистка экрана
                    //отрисовка и ввод данных
                if (player == BoT)
                {
                    //system("cls");//отчистка экрана
                    //printf("B O T");
                    //_getch();
                    shot_position1 = BOT(sea, p_data, m, a, b);
                    target_x = shot_position1 * 2;
                    target_y = shot_position1 >> 8;
                    shot_position = (target_y << 8) | (target_x);
                    draw_field(p_data, p_dataP, shot_position, 0, BotName);
                    game_state = PROCESSING;//переключаем игрока
                }
                else
                {
                    draw_field(p_data, p_dataP, shot_position, tmp1, BotName);

                    if (get_target_possition(&target_x, &target_y)) //нажат enter(выстрел)
                    {
                        game_state = PROCESSING;//переключаем игрока
                    }
                    shot_position = (target_y << 8) | (target_x);
                }
                break;
            }
            case PROCESSING:
            {
                if (player == PLAYER_1)
                {
                    
                    if (shot_analiz(p_dataP, bot_data, target_x / 2, target_y, score, tmp1))
                    {
                        //_getch();
                        if (score[tmp1] == 20)
                        {
                            system("cls");//отчистка экрана
                            printf("PLAYER %s WIN!!!", name);
                            isRun = 0;
                        }
                        else
                        {
                            if (s == 20)
                            {
                                system("cls");//отчистка экрана
                                printf("BOT WIN!!!");
                                isRun = 0;
                            }
                            game_state = DRAW;
                        }
                    }
                    else
                    {
                        //_getch();
                        player = BoT;
                        game_state = DRAW;
                    }
                    analiz(bot_data, p_dataP, target_x / 2, target_y, ship);
                }
                else
                {
                    if (shotBOT_analiz(p_data, target_x / 2, target_y, score, tmp1))
                    {
                        //_getch();
                        if (score[tmp1] == 20)
                        {
                            system("cls");//отчистка экрана
                            printf("YOU WIN!!!");
                            Sleep(2000);
                            isRun = 0;
                        }
                        else
                        {
                            if (s == 20)
                            {
                                system("cls");//отчистка экрана
                                printf("BOT WIN!!!");
                                Sleep(2000);
                                isRun = 0;
                            }
                            game_state = DRAW;
                        }
                    }
                    else
                    {
                        //_getch();
                        player = PLAYER_1;
                        game_state = DRAW;
                    }
                }


                break;
            }

            }
            case EXIT:
            {
                break;
            }      
        }
        case DEC2:
        {
            recv(client, message, sizeof(message), 0);
            printf("%s\n", message);
            if (strcmp(message, "Your opponent:") == 0) {
                recv(client, message, sizeof(message), 0);
                strcpy(opponentName, message);
                printf("%s\n", message);
            }
            if (strcmp(message, "Not enouth players") == 0) {
                printf("1 - play with the bot\n2 - wait for another player\n");
                gets_s(chose);
                send(client, chose, strlen(chose), 0);
                if (strcmp(chose, "2") == 0) {
                    while (1) {
                        recv(client, message, sizeof(message), 0);
                        if (strcmp(message, "Your opponent:") == 0) {
                            printf("%s\n", message);
                            recv(client, message, sizeof(message), 0);
                            strcpy(opponentName, message);
                            printf("%s\n", opponentName);
                            break;
                        }
                    }
                }
                else {
                    clientChoise = DEC1;
                    break;
                }
            }
            tmp1 = 1;
            //printf("Arrange the boats\nEnter: R - random, M - ?\n");
            while (1) {
                switch (game_state)
                {
                case INIT1:
                {
                    //порядок действий по инициализации игры ИГРОКА№1
                    ship_generate(p_data, ship);
                    game_state = DRAW1;
                    break;
                }
                case DRAW1:
                {
                    system("cls");//отчистка экрана
                    //отрисовка и ввод данных
                    draw_field(p_data, p_dataP, shot_position, 0, opponentName);
                    printf("Are you satisfied with the arrangement?\n");
                    printf("press the space bar if you want to change the location of the ships / press enter to continue");
                    switch (_getch())
                    {
                    case KEY_ENTER:
                    {
                        if (step == 1)
                            game_state = DRAW;
                        else {
                            system("cls");
                            draw_field(p_data, p_dataP, shot_position, tmp1, opponentName);
                            game_state = WAITING;
                        }
                        break;
                    }
                    case FIRE:
                    {

                        game_state = INIT1;
                        break;
                    }
                    }
                    break;
                }
                case DRAW:
                {
                    char x[2], y[2];
                    char symb[2];
                    system("cls");//отчистка экрана
                    //отрисовка и ввод данных
                    draw_field(p_data, p_dataP, shot_position, tmp1, opponentName);
                    if (step == 1) {
                        if (get_target_possition(&target_x, &target_y)) //нажат enter(выстрел)
                        {

                            sprintf(x, "%c", target_x);
                            ret = send(client, x, 2, 0);
                            sprintf(y, "%c", target_y);
                            ret = send(client, y, 2, 0);
                            recv(client, symb, 3, 0);
                            
                            if (strcmp(symb, "*") == 0) {
                                p_dataP[target_y * 10 + target_x / 2] = SHOT;
                                step = 0;
                                printf("%s's move\n", opponentName);
                                game_state = WAITING;
                                break;
                            }
                            if (strcmp(symb, "X") == 0)
                                p_dataP[target_y * 10 + target_x / 2] = STRIKE;
                            if (strcmp(symb, "-") == 0) {
                                system("cls");
                                printf("YOU WIN\n");
                                Sleep(2000);
                                clientChoise = EX;
                                break;
                            }
                            //Sleep(1000);
                        }
                        shot_position = (target_y << 8) | (target_x);
                    }
                    else {
                        game_state = WAITING;
                        break;
                    }

                    break;
                }
                case WAITING:
                {
                    char x[2], y[2];
                    recv(client, message, sizeof(message), 0);
                    if (strcmp(message, "ok") == 0) {
                        ret = recv(client, x, 2, 0);
                        ret = recv(client, y, 2, 0);
                        target_x = x[0];
                        target_y = y[0];
                        game_state = PROCESSING;
                    }
                    break;
                }
                case PROCESSING:
                {
                    //обработка данных
                    //....
                    printf("%d,%d", target_x / 2, target_y);
                    //shot_analiz(tmpP, tmp, target_x / 2, target_y, flag);
                    //_getch();
                    if (shot_analiz(p_dataP, p_data, target_x / 2, target_y, score, tmp1))
                    {
                        //_getch();
                        if (score[tmp1] == 20)
                        {
                            send(client, "-", 2, 0);
                            system("cls");//отчистка экрана
                            printf("%s WIN!!!", opponentName);
                            Sleep(2000);
                            closesocket(client);
                        }
                        else
                        {
                            send(client, "X", 2, 0);
                            system("cls");
                            draw_field(p_data, p_dataP, shot_position, tmp1, opponentName);
                            game_state = WAITING;
                            break;
                        }
                    }
                    else
                    {
                        send(client, "*", 2, 0);
                        step = 1;
                        game_state = DRAW;
                    }

                    break;
                }
                
                case EXIT:
                {
                    break;
                }
                }
            }
        }
        case EX:
        {
            break;
        }
        }
    }

    closesocket(client);
}

int main()
{
    WSADATA wsd;
    if (WSAStartup(MAKEWORD(1, 1), &wsd) != 0)
    {
        printf("Can't connect to socket lib");
        return 1;
    }
    SendData2Server();
    Sleep(5000);
    printf("Session is closed\n");
    return 0;
}
