#ifndef INTERFACE_H
#define INTERFACE_H
#include<stdio.h>
#include"cursor-control.h"
#include<conio.h>
#include"tools.h"
ITEM move_top(ITEM pos, int mode) {
    ITEM pos1 = pos;
    if(pos1.row==0) 
    {
        set_to_start();
        return pos1;
    }
    leave_point(pos1);
    pos1.row-=1;
    set_to_point(pos1);
    Sleep(500);
    return pos1;
}
ITEM move_down(ITEM pos, int mode) {
    ITEM pos1 = pos;
    if(pos1.row==mode-1)
    {
        set_to_start();
        return pos1;
    }
    leave_point(pos1);
    pos1.row+=1;
    set_to_point(pos1);
    Sleep(500);
    return pos1;
}
ITEM move_right(ITEM pos, int mode) {
    ITEM pos1 = pos;
    if(pos1.column==mode-1)
    {
        set_to_start();
        return pos1;
    }
    leave_point(pos1);
    pos1.column+=1;
    set_to_point(pos1);
    Sleep(500);
    return pos1;
}
ITEM move_left(ITEM pos, int mode) {
    ITEM pos1 = pos;
    if(pos1.column==0)
    {
        set_to_start();
        return pos1;
    }
    leave_point(pos1);
    pos1.column-=1;
    set_to_point(pos1);
    Sleep(500);
    return pos1;
}
int find_marked(ITEM pos,int ** marked,int hide){
    for(int i = 0;i<hide;i++){
        if(pos.column == *(*(marked+i)+1) && pos.row == **(marked+i)) return i;
    }
    return -1;
}
void game(int ** sudoku, int mode, int hide) {
    print_sudoku(sudoku,mode);
    printf("\"e\" - to enter, \"q\" - to quit, \"wasd\" - to move");
    int solved[hide], count = 0;
    ITEM pos = generate_item(-1,0,0,mode);
    set_to_point(pos);
    for(int i = 0; i<hide;i++) {
        *(solved+i) = 0;
    }
    char c;
    int end = 0;
    int ** marked = get_positions(sudoku,mode,hide);
    
    int changed = 0;
    while(count<hide){
        c = getch();
        switch (c)
        {
        case 'w': case 'W':
            pos = move_top(pos,mode);
            printf("  Right: %d, All: %d ",count,hide);
            break;
        case 's': case 'S':
            pos = move_down(pos,mode);
            printf("  Right: %d, All: %d ",count,hide);
            break;
        case 'd': case 'D':
            pos = move_right(pos,mode);
            printf("  Right: %d, All: %d ",count,hide);
            break;
        case 'a': case 'A':
            pos = move_left(pos,mode);
            printf("  Right: %d, All: %d ",count,hide);
            break;
        case 'e':
            if(find_marked(pos,marked,hide) >= 0 && pos.value!=0) {
                insert_to(sudoku,pos,mode);
                changed = 1;
                printf(" ");
            }
            else printf("%d, %d",find_marked(pos,marked,hide),pos.value);
            break;
        case 'q':
            end = 1;
            break;
        case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
        if(c-'0' <= mode) pos.value = c-'0';
        else pos.value = 0;
        printf("Current: %d",pos.value);
        default:
            break;
        }
        if(find_marked(pos,marked,hide) >= 0) {
            if( is_in_column(pos,sudoku) == 0 && is_in_row(pos,sudoku) == 0 && is_in_square(pos,sudoku) == 0){
                if(*(*(marked+find_marked(pos,marked,hide))+2) == 0 && changed == 1) {
                    count++;
                    *(*(marked+find_marked(pos,marked,hide))+2) = 1;
                    
                }
            }
            else {
            if(*(*(marked+find_marked(pos,marked,hide))+2) == 1 && changed == 1) {
                    count--;
                    *(*(marked+find_marked(pos,marked,hide))+2) = 0;
                    
                }
            }
            //printf("    %d    ", )
        }
        changed = 0;
        if(end == 1) break;
        
    }
    set_to_end(mode);
    if(end == 1) printf("Maybe next time(");
    else printf("You won!!!");
    free_matrix(marked,hide);
}
#endif
