#ifndef TOOLS_H
#define TOOLS_H
#define ITEM struct Item
#include<stdio.h>
#include<windows.h>
    struct Item {
        int value;
        int row;
        int column;
        int mode;
        int square;
        int square_size;
    };


    struct Item generate_item(int value, int row,int column,int mode) {
        struct Item item;
        item.value = value;
        item.row = row;
        item.column = column;
        item.mode = mode;
        int square = 0;
        if(mode == 4){
            item.square_size = 2;
            if(row > 1) square+=2;
            if(column>1) square+=1;
        }
        else{
            item.square_size = 3;
            if(row > 5) square+=6;
            else if(row > 2) square+=3;
            if(column > 5) square+=2;
            else if(column > 2) square+=1;
        }
        item.square = square;
        return item;
    }
    int is_in_row(struct Item item, int ** sudoku){
        int answer = 0;
        for(int i = 0;i<item.mode;i++){
            if(item.value == *(*(sudoku+item.row)+i) && (item.column != i)) {
                answer = 1;
            }
        }
        return answer;
    }
    int is_in_column(struct Item item,int ** sudoku) {
        int answer = 0;
        for(int i = 0;i<item.mode;i++){
            if((item.value == *(*(sudoku+i)+item.column)) && (item.row != i)){
                answer = 1;
            }
        }
        return answer;
    }
    int is_in_square(struct Item item, int ** sudoku){
        int answer = 0;
        //puts("12\n");
            for (int i = item.row-(item.row%item.square_size); i<item.square_size+item.row-(item.row%item.square_size);i++){
                for(int j = item.column-(item.column%item.square_size); j<item.square_size+item.column-(item.column%item.square_size);j++) {
                    if (*(*(sudoku+i)+j) == item.value && (i!=item.row) && (j!=item.column)){
                        //printf("i: %d, j: %d, row: %d, col: %d\n",i,j,item.row,item.column);
                        answer = 1;
                    }
                }
            }
        return answer;
    }
    void print_sudoku(int ** sudoku, int mode) {
        puts("\n");
        for(int i = 0; i<mode;i++){
            for(int j = 0;j<mode;j++) {
                if (*(*(sudoku+i)+j) == 0) printf("   .");
                else printf("%4d",*(*(sudoku+i)+j));
            }
            puts("\n");
        }
    }
    int ** get_positions(int** sudoku, int mode, int hide) {
        int ** pos = (int**) calloc(hide, sizeof(int*));
        int g = 0;
        for (int i = 0; i< hide;i++){
            *(pos+i) =(int*) calloc(3,sizeof(int));
        }
        for(int i = 0; i<mode;i++){
            for(int j = 0;j<mode;j++){
                if(*(*(sudoku+i)+j) == 0) {
                    *(*(pos+g)) = i;
                    *(*(pos+g)+1) = j;
                    *(*(pos+g)+2) = 0;
                    g++;
                }
            }
        }
        return pos;
    }
    void free_matrix(int**sudoku,int mode){
    for(int i = 0;i<mode;i++){
        free(*(sudoku+i));
    }
    free(sudoku);
    }
    #endif