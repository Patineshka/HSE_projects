#include "Tree.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// функция создает узел для списка
NODE* CreatList(int freq, int i){
    NODE* value = (NODE*)malloc(sizeof(NODE));
    value->freq = freq;
    value->left = value->right = 0;
    value->symb = i;
    value->isSymb = 1;
    strcpy(value->code, "");
    return value;
}

// функция соединяет узлы в односвязный список по частоте вхождени символов
void Add2List(NODE** pphead, NODE* value)
{
    while (*pphead){
        if ((*pphead)->freq > value->freq)
            break;
        pphead = &((*pphead)->next);
    }
    value->next = *pphead;
    *pphead = value;
}

NODE * MakeNodeFromNode(NODE * left, NODE * right)
{
    NODE * res = (NODE*)malloc(sizeof(NODE));
    res->freq = left->freq + right->freq;
    res->symb = 0;
    res->left = left;
    res->right = right;
    res->next = 0;
    res->isSymb = 0;
    strcpy(res->code, "");
    return res;
}


NODE * MakeTreeFromList(NODE * head)
{
    while (head && head->next){
        NODE * left = head;
        NODE * right = head->next;
        Add2List(&(head->next->next), MakeNodeFromNode(left, right));
        head = head->next->next;
    }
    return head;
}

void encode(NODE* root)
{
    if (!root->left && !root->right && strcmp(root->code, "") == 0)
        strcat(root->code, "0");
    if (root->left) {
        strcpy(root->left->code, root->code);
        strcat(root->left->code, "0");
        encode(root->left);
    } if (root->right){
        strcpy(root->right->code, root->code);
        strcat(root->right->code, "1");
        encode(root->right);
    }
}

// функция формирует из строки бит строку символов
void Code(FILE* code, BIT2CHAR symb, int len, FILE* comp){
    fseek(code, 0, SEEK_SET);
    for (int i = 0; i < len; ++i){
        symb.mbit.b1 = fgetc(code);
        symb.mbit.b2 = fgetc(code);
        symb.mbit.b3 = fgetc(code);
        symb.mbit.b4 = fgetc(code);
        symb.mbit.b5 = fgetc(code);
        symb.mbit.b6 = fgetc(code);
        symb.mbit.b7 = fgetc(code);
        symb.mbit.b8 = fgetc(code);
        putc(symb.symb, comp);
    }
}

void MakeTreeFromFile(NODE* head, FILE* in, int start, NODE* root, int beginStr, int k){
    head->right = head->left = 0;
    while (k != beginStr) {
        fseek(in, start, SEEK_SET);
        char ch = (char) fgetc(in);
        char next = (char) fgetc(in);
        char next2 = (char) fgetc(in);
        NODE* new = (NODE*)malloc(sizeof(NODE));
        new->freq = ch - '0';
        if (ch == '0' && (next != '\n' || next2 == '\n')) {
            if (head->left == 0)
                head->left = new;
            head->left->freq = ch - '0';
            head = head->left;
            start++;
        } else if (ch == '1' && (next != '\n' || next2 == '\n')) {
            if (head->right == 0)
                head->right = new;
            head->right->freq = ch - '0';
            head = head->right;
            start++;
        } else if (ch != '\n' || next == '\n') {
            head->symb = ch;
            head->right = head->left = 0;
            head = root;
            start++;
        } else{
            start++;
            k++;
        }
    }
}

void decode(NODE* root, FILE* Str, FILE* in, int start, NODE* head, int end) {
    fseek(Str, 0, SEEK_SET);
    while (start != end) {
        fseek(Str, start, SEEK_SET);
        char ch = (char) fgetc(Str);
        if (ch == '0') {
            if (root->left) {
                start++;
                root = root->left;
            }if (!root->left) {
                fputc(root->symb, in);
                root = head;
            }
        }if (ch == '1') {
            if (root->right) {
                start++;
                root = root->right;
            }if (!root->right){
                fputc(root->symb, in);
                root = head;
            }
        }
    }
}