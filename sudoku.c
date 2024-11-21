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
    system("cls");
    puts("4 - 4x4, 9 - 9x9");
    scanf("%d",&mode);
    int ** sudoku = generate_null_matrix(mode);
    sudoku = generate_sudoku(sudoku,mode);
    puts("\n");
    int hide = create_task(sudoku,mode);
    system("cls");
    print_sudoku(sudoku,mode);
    puts("1 - brutforce, -1 - game");
    int decision = 0; scanf("%d",&decision);
    puts("press any button to start");
    getch();
    int ** pos = get_positions(sudoku,mode,hide);
    system("cls");
    puts("\n");
    if(decision == 1) brutforce(sudoku,mode,hide);
    else game(sudoku,mode,hide);
    puts("\n");
    // for (int i = 0;i<hide;i++){
    //     printf("(%d, %d) ",*(*(pos+i)),*(*(pos+i)+1));
    // }
    free_matrix(sudoku,mode);
    return 0;
}