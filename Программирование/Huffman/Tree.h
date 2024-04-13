#pragma once
#define CODE_SIZE 255
#include <stdio.h>

typedef struct node {
    unsigned char symb; //
    unsigned int freq; //
    int isSymb; //
    char code[CODE_SIZE]; //
    struct node *left, *right, *next;
}NODE;

typedef union bit2char {
    char symb;
    struct bit {
        unsigned b1 : 1;
        unsigned b2 : 1;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
        unsigned b7 : 1;
        unsigned b8 : 1;
    }mbit;
}BIT2CHAR;

NODE* CreatList(int value, int i);
void Add2List(NODE** pphead, NODE* value);
NODE* MakeNodeFromNode(NODE * left, NODE * right);
NODE * MakeTreeFromList(NODE * head);
void encode(NODE* root);
void Code(FILE* code, BIT2CHAR symb, int len, FILE* comp);
void MakeTreeFromFile(NODE* head, FILE* in, int start, NODE* root, int BeginStr, int k);
void decode(NODE* root, FILE* str, FILE* in, int start, NODE* head, int end);