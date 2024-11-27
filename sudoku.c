#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>
#include"cursor-control.h"
#include"tools.h"
#include"generate.h"
#include"interface.h"
#include"brutforce.h"




int main(){
    srand(time(NULL));
    int mode;
    // Очистка консоли и ввод размера судоку
    system("cls");
    puts("4 - 4x4, 9 - 9x9");
    scanf("%d",&mode);
    // генерация судоку
    int ** sudoku = generate_null_matrix(mode);
    sudoku = generate_sudoku(sudoku,mode);
    puts("\n");
    int hide = create_task(sudoku,mode);
    // вывод судоку и выбор режима
    system("cls");
    print_sudoku(sudoku,mode);
    puts("1 - brutforce, -1 - game");
    int decision = 0; scanf("%d",&decision);
    puts("press any button to start");
    getch();
    int ** pos = get_positions(sudoku,mode,hide);
    system("cls");
    puts("\n");
    // начало брутфорса или игры
    if(decision == 1) brutforce(sudoku,mode,hide);
    else game(sudoku,mode,hide);
    puts("\n");
    // освобождение выделенного места
    free_matrix(sudoku,mode);
    return 0;
}
