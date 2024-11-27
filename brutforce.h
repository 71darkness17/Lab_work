#ifndef BRUTFORCE_H
#define BRUTFORCE_H
#include<stdio.h>
#include<stdlib.h>
#include"tools.h"
#include"cursor-control.h"
// функция брутфорса
void brutforce(int ** sudoku, int mode, int hide) {
    print_sudoku(sudoku,mode); // вывод всей судоку
    int already_used[hide][mode]; // уже использованные значения для определенной ячейки
    for (int i = 0; i<hide;i++){
        for(int j = 0;j<mode;j++){
            already_used[i][j] = 0;
        }
    }
    int digits[mode]; // массив цифр от 1 до режима игры
    for (int i = 0;i<mode;i++){
        digits[i]=i+1;
    }
    int ids[hide];
    int ** pos = get_positions(sudoku,mode,hide); // массив с координатами пропусков
    int i=0;
    // цикл перебора
    while(i<hide){
        struct Item item = generate_item(1,*(*(pos+i)),*(*(pos+i)+1),mode); // создание структуры текущей ячейки
        insert_to(sudoku, item,mode); // изменение значения текущей ячейки на 1
        Sleep((10-mode)*20);
        int g = 0; // счетчик попыток подобрать элемент
        int h = 0; // счетчик чтобы не проверялись цифры больше чем режим работы
        // подбор элемента и проверка значения
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
        // переход назад если не получилось подобрать
        if (g>10){
            *(*(sudoku+item.row)+item.column) = 0;
            for(int k = 0;k<mode;k++){
                already_used[i][k] = 0;
            }
            i--;
            if(i<0) break;
        }
        // переход вперед если подобрано успешно
        else{
            *(*(sudoku+item.row)+item.column) = item.value;
            already_used[i][item.value-1] = 1;
            i++;
        }
    }
    // освобождение вспомогательного массива
    free_matrix(pos,hide);
    
}
#endif
