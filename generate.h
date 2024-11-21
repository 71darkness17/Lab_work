#ifndef GENERATE_H
#define GENERATE_H
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include"tools.h"

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


void null_row(int * row, int mode) {
    for (int i = 0;i<mode;i++){
        *(row+i) = 0;
    }
}
void null_matrix(int ** sudoku, int mode){
    for(int i =0;i<mode;i++){
        null_row(*(sudoku+i),mode);
    }
}
int ** generate_sudoku(int ** sudoku, int mode){
    int ready = 0,counter = 0;;
    while(ready == 0) {
        ready = 1;
        for(int i = 0; i<mode;i++){
            if (ready == 0){
                i--;
                null_row(*(sudoku+i),mode);
                ready = 1;
                counter++;
                if(counter >15) {
                    
                }
            }
            for (int j = 0;j<mode;j++){
                struct Item item = generate_item(rand()%mode + 1,i,j,mode);
                int g = 0;
                while(is_in_column(item,sudoku) == 1 || is_in_row(item,sudoku) == 1 || is_in_square(item,sudoku) == 1){
                    item.value = rand()%mode + 1;
                    if(++g>100) break;
                }
                if (g>100){
                    ready = 0;
                    //puts("fail\n");
                    //print_sudoku(sudoku,mode);
                    break;
                }
                //printf("\n\n\n%d",item.value);
                *(*(sudoku+i)+j) = item.value;
            }
            //if (ready == 1) break;
        }
    }
    return sudoku;
}

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