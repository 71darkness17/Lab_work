#ifndef GENERATE_H
#define GENERATE_H
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"tools.h"
// генерация матрицы с нулями
int ** generate_null_matrix(int mode){
    int ** sudoku = (int**) calloc(mode,sizeof(int*));
    for(int i = 0;i<mode;i++) {
        *(sudoku+i) = (int*) calloc(mode,sizeof(int));
        for(int j = 0; j<mode; j++){
            *(*(sudoku+i)+j) = 0;
        }
    }
    return sudoku;
}

// замена всех значений строки на нули
void null_row(int * row, int mode) {
    for (int i = 0;i<mode;i++){
        *(row+i) = 0;
    }
}
// замена всех значений матрицы на нули
void null_matrix(int ** sudoku, int mode){
    for(int i =0;i<mode;i++){
        null_row(*(sudoku+i),mode);
    }
}
//генерация судоку
int ** generate_sudoku(int ** sudoku, int mode){
    int ready = 0,counter = 0; // флаг того готова ли судоку и счетчик обнулений строк
    while(ready == 0) {
        ready = 1;
        for(int i = 0; i<mode;i++){
            if (ready == 0){ // обнуление строки если не удается ее создать
                i--;
                null_row(*(sudoku+i),mode);
                ready = 1;
                counter++;
                if(counter >15) {
                    
                }
            }
            for (int j = 0;j<mode;j++){
                struct Item item = generate_item(rand()%mode + 1,i,j,mode); // создание структуры для текущего элемента
                int g = 0;
                // перебор значений для ячейки с постоянной проверкой
                while(is_in_column(item,sudoku) == 1 || is_in_row(item,sudoku) == 1 || is_in_square(item,sudoku) == 1){
                    item.value = rand()%mode + 1;
                    if(++g>100) break;
                }
                if (g>100){
                    ready = 0; // высставление отметки о том что нужно обнулить строку
                    break;
                }
                *(*(sudoku+i)+j) = item.value; // присвоение ячейке значения
            }
        }
    }
    return sudoku;
}
// создание пропусков в судоку, возвращает количество созданных пропусков
int create_task(int ** sudoku,int mode){
    int cnt = 0;
    for(int i = 0; i<mode;i++){
        for(int j = 0;j<mode;j++){
            if(rand()%(3+mode%4) == 0) {
                *(*(sudoku+i)+j) = 0;
                cnt++;
            }
        }
    }
    return cnt;
}
#endif
