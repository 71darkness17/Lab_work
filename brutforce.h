#ifndef BRUTFORCE_H
#define BRUTFORCE_H
#include<stdio.h>
#include<stdlib.h>
#include"tools.h"
#include"cursor-control.h"
void brutforce(int ** sudoku, int mode, int hide) {
    print_sudoku(sudoku,mode);
    int already_used[hide][mode];
    for (int i = 0; i<hide;i++){
        for(int j = 0;j<mode;j++){
            already_used[i][j] = 0;
        }
    }
    int digits[mode];
    for (int i = 0;i<mode;i++){
        digits[i]=i+1;
    }
    int ids[hide];
    int ** pos = get_positions(sudoku,mode,hide);
    int i=0;
    while(i<hide){
        struct Item item = generate_item(1,*(*(pos+i)),*(*(pos+i)+1),mode);
        insert_to(sudoku, item,mode);
        Sleep((10-mode)*20);
        int g = 0;
        int h = 0;
        while(is_in_column(item,sudoku) == 1 || is_in_row(item,sudoku) == 1 || is_in_square(item,sudoku) == 1 || already_used[i][item.value-1] == 1){
            item.value = digits[h];
            
            *(*(sudoku+item.row)+item.column) = item.value;
            
            
            insert_to(sudoku, item,mode);
            Sleep((10-mode)*20);
            g++;
            if(g>10) break;
            h++;
            if(h>=mode) h = 0;
        }
        if (g>10){
            *(*(sudoku+item.row)+item.column) = 0;
            for(int k = 0;k<mode;k++){
                already_used[i][k] = 0;
            }
            i--;
            if(i<0) break;
        }
        else{
            *(*(sudoku+item.row)+item.column) = item.value;
            already_used[i][item.value-1] = 1;
            i++;
        }
    }
    
    free_matrix(pos,hide);
    
}
#endif