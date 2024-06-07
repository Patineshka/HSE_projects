#define HAVE_STRUCT_TIMESPEC
#define _CRT_SECURE_NO_WARNINGS
#include <pthread.h>
#pragma comment(lib, "ws2_32.lib")
#include <winsock.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>

typedef enum
{
    DEC1 = 0
    , DEC2

}CONDITION;

pthread_mutex_t mutex;
pthread_mutex_t mutex_file;

typedef struct infClient {
    char name[100];
    char choise[3];
    int inPlay; 
    char x[3];
    char y[3];
    int step;
}INFclient;

int numberOfPlayers;
INFclient players[100] = {0};

void* ClientStart(void* param)
{
    SOCKET client = (SOCKET)param;  
    int ret;

    char name[50];
    ret = recv(client, name, 50, 0);
    name[ret] = '\0';
    int count = numberOfPlayers;
    strcpy(players[numberOfPlayers++].name, name);
    
    char choise[3];
    ret = recv(client, choise, 3, 0);
    choise[ret] = '\0';
    strcpy(players[numberOfPlayers-1].choise, choise);

    CONDITION clientChoise = ((strcmp(choise, "2") == 0)) ? DEC2 : DEC1;

    while (1) 
    {
        switch (clientChoise)
        {
        case DEC1:
        {
            return 0;
        }
        case DEC2:
        {
            /*if (players[0].numberOfClient > 2) {
                ret = send(client, "Choose the opponent:", sizeof("Choose the opponent:"), 0);
                for (int i = 0; i < players[0].numberOfClient; ++i) {
                    if (strcmp(players[i].name, name) != 0)
                        ret = send(client, players[i].name, sizeof(players[i].name), 0);
                }
            }*/
            int opponent;
            if (numberOfPlayers == 2) {
                for (int i = 0; i < numberOfPlayers; ++i) {
                    if (strcmp(players[i].name, name) != 0)
                        opponent = i;
                }
                ret = send(client, "Your opponent:", sizeof("Your opponent:"), 0);
                ret = send(client, players[opponent].name, sizeof(players[opponent].name), 0);
            }
            if (numberOfPlayers == 1) {
                players[count].step = 1;
                ret = send(client, "Not enouth players", sizeof("Not enouth players"), 0);
                ret = recv(client, choise, 3, 0);
                if (strcmp(choise, "2") == 0) {
                    while (1)
                        if (numberOfPlayers == 2 && strcmp(players[1].choise, "2") == 0) {
                            ret = send(client, "Your opponent:", sizeof("Your opponent:"), 0);
                            ret = send(client, players[1].name, sizeof(players[1].name), 0);
                            opponent = 1;
                            break;
                        }
                }
                else {
                    clientChoise = DEC1;
                    break;
                }
            }
            while (1) {
                char x[1], y[1];
                if (players[count].step == 1 && players[opponent].step == 0) {
                    ret = recv(client, x, 1, 0);
                    ret = recv(client, y, 1, 0);
                    x[ret] = '\0';
                    y[ret] = '\0';
                    strcpy(players[count].x, x);
                    strcpy(players[count].y, y);
                    players[count].step = 0;
                    players[opponent].step = 1;
                }
                if (players[count].step == 0 && players[opponent].step == 1) {
                    ret = send(client, players[opponent].x, 1, 0);
                    ret = send(client, players[opponent].y, 1, 0);
                    players[count].step = 1;
                    players[opponent].step = 0;
                }
            }

            return 0;
        }
        }
    }

}

// надо как то прописать кто идет первым и пока например игрок1 не походил, игрок2 не может ходить
// 
int CreateServer()
{
    SOCKET server, client;
    sockaddr_in localaddr, clientaddr;
    int size;
    
    server = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (server == INVALID_SOCKET)
    {
        printf("Error create server\n");
        return 1;
    }
    localaddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    localaddr.sin_family = AF_INET;
    localaddr.sin_port = htons(2097);//port number is for example, must be more than 1024
    if (bind(server, (struct sockaddr*)&localaddr, sizeof(localaddr)) == SOCKET_ERROR)
    {
        printf("Can't start server\n");
        return 2;
    }
    else
    {
        printf("Server is started\n");
    }
    listen(server, 50);//50 клиентов в очереди могут стоять
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex_file, NULL);
    while (1)
    {
        size = sizeof(clientaddr);
        client = accept(server, (struct sockaddr*)&clientaddr, &size);
        if (client == INVALID_SOCKET)
        {
            printf("Error accept client\n");
            continue;
        }
        else
        {
            printf("Client is accepted\n");
        }
        pthread_t mythread;
        int status = pthread_create(&mythread, NULL, ClientStart, (void*)client);
        pthread_detach(mythread);
    }
    pthread_mutex_destroy(&mutex_file);
    pthread_mutex_destroy(&mutex);
    printf("Server is stopped\n");
    closesocket(server);

    return 0;
}

int main()
{
    WSADATA wsd;
    if (WSAStartup(MAKEWORD(1, 1), &wsd) == 0)
    {
        printf("Connected to socket lib\n");
    }
    else
    {
        return 1;
    }
    return CreateServer();
}

