#ifndef CURSOR_CONTROL_H
#define CURSOR_CONTROL_H
#include<stdio.h>
#include<windows.h>
#include"tools.h"
#define POS       struct Position
struct Position {
    int row;
    int column;
};
void set_color(int color){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if(color ==1) SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
    else SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
struct Position generate_position(int column,int row){
    struct Position a;
    a.row = row;
    a.column = column;
    return a;
}
void set_to_start(){
    HANDLE handle;
    COORD coord;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition (handle , coord);
}
void set_to_end(int mode) {
    HANDLE handle;
    COORD coord;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = 0;
    coord.Y = 4 + 2*(mode+1);
    SetConsoleCursorPosition (handle , coord);
}
void set_to_point(ITEM pos){
    HANDLE handle;
    COORD coord;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = 4*pos.column + 3;
    coord.Y = 4 + 2*pos.row;
    SetConsoleCursorPosition (handle , coord);
    coord.X--;
    SetConsoleCursorPosition (handle , coord);
    printf("[");
    coord.X+=2;
    SetConsoleCursorPosition (handle , coord);
    printf("]");
    set_to_start();
    
}
void leave_point(ITEM pos) {
    HANDLE handle;
    COORD coord;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = 4*pos.column + 3;
    coord.Y = 4 + 2*pos.row;
    SetConsoleCursorPosition (handle , coord);
    coord.X--;
    SetConsoleCursorPosition (handle , coord);
    printf(" ");
    coord.X+=2;
    SetConsoleCursorPosition (handle , coord);
    printf(" ");
    set_to_start();
}
void insert_to(int ** sudoku,ITEM pos, int mode) {
    HANDLE handle;
    COORD coord;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coord.X = 4*pos.column + 3;
    coord.Y = 4 + 2*pos.row;
    SetConsoleCursorPosition (handle , coord);
    *(*(sudoku+pos.row)+pos.column) = pos.value;
    set_color(1);
    printf("%d",pos.value);
    set_color(0);
    set_to_start();
    
}
#endif