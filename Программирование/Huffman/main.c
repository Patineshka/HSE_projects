#include "Tree.h"

#include <stdio.h>
#include <stddef.h>
#include <malloc.h>
#include <string.h>

#define SIZE 256

int main()
{
    int freq[SIZE] = {0};
    int NumberOfSymbols = 0;
    printf("Input Filename\n");
    char FileName[SIZE] = {0};
    gets(FileName);
    FILE *SourceFile = fopen(FileName, "rb");
    if (!SourceFile){
        printf("Error open file for reading\n");
        return -1;
    }
    // Определение частоты вхождений каждого символа
    fseek(SourceFile, 0L, SEEK_END);
    int length = ftell(SourceFile);
    fseek(SourceFile, 0, SEEK_SET);
    for (int i = 0; i < length; ++i) {
        if (++freq[(unsigned char) fgetc(SourceFile)] == 1) {
            NumberOfSymbols++;
        }
    }
    // Построение списка, упорядоченного по частоте
    NODE* phead = NULL;
    for (int i = 0; i < 256; ++i){
        if (freq[i] != 0) {
            Add2List(&phead, CreatList(freq[i], i));
        }
    }

    // Построение дерева Хоффмана на основе списка
    NODE* root = MakeTreeFromList(phead);
    // Получение кода Хоффмана для каждого символа
    encode(root);
    // Создение файлов для записи  и ...
    char CompFileName[SIZE] = "compressed.";
    strcat(CompFileName, FileName);
    FILE *CompressedFile = fopen(CompFileName, "wb+");
    char CodeFileName[SIZE] = "code.";
    strcat(CodeFileName, FileName);
    FILE * CodeFile =  fopen(CodeFileName, "wb+");
    // Замена символов на их код
    fseek(SourceFile, 0, SEEK_SET);
    NODE* phead1 = phead;
    for (int i = 0; i < length; ++i) {
        unsigned char asc = (unsigned char) fgetc(SourceFile);
        while (phead->symb != asc || phead->isSymb == 0){
            phead = phead->next;
        }
        fputs(phead->code, CodeFile);
        phead = phead1;
    }
    //
    fprintf(CodeFile, "\nsymbols = %c\n", NumberOfSymbols - 1);
    int k = 0;
    while (k < NumberOfSymbols){
        if (phead->isSymb == 1){
            fputs(phead->code, CodeFile);
            fputc(phead->symb, CodeFile);
            fputs("\n", CodeFile);
            k++;
        }
        phead = phead->next;
    }
    // Формирование из строки бит строки символов и запись в файл
    int lenBinStr = ftell(CodeFile);
    int len = lenBinStr / 8 + 1;
    BIT2CHAR symb;
    Code(CodeFile, symb, len, CompressedFile);
    printf("Compression is complete\n");
    // Чтение файла с кодом и формирование дерева
    fseek(CodeFile, lenBinStr + 11, SEEK_SET);
    int start = fgetc(CodeFile) + 1;
    NODE* head = (NODE*)malloc(sizeof(NODE));
    MakeTreeFromFile(head, CodeFile, lenBinStr + 13, head, start, 0);
    printf("Decompression is underway\n");
    // Декодирование и запись в файл распаковки
    char UncompressedFileName[SIZE] = "uncompressed.";
    strcat(UncompressedFileName, FileName);
    FILE *UncompressedFile = fopen(UncompressedFileName, "wb+");
    decode(head, CodeFile, UncompressedFile, 0, head, lenBinStr);
    printf("Decompression is complete\n");
    // Закрытие файлов
    fclose(UncompressedFile);
    fclose(CodeFile);
    fclose(SourceFile);
    fclose(CompressedFile);
}












// Определение частоты вхождений каждого символа, построение списка, упорядоченного по частоте(функции CreateList, Add2List) - Серафим
// Построение дерева Хаффмана на основе связного списка и получение кода для каждого символа (функции MakeNodeFromNode, MakeTreeFromList, encode) - Катя
// Замена символов на их код, формирование из строки бит строку символов и запись в файл сжатия (функция Code) - Маша
// Декодирование и запись в файл распаковки, декодирование и запись в файл распаковки (функция MakeTreeFromFile, decode) - Патина
