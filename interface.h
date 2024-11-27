#ifndef INTERFACE_H
#define INTERFACE_H
#include<stdio.h>
#include"cursor-control.h"
#include<conio.h>
#include"tools.h"
// Передвигает курсов вверх
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
// Передвигает курсор вниз
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
// Передвигает курсор вправо
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
// Передвигает курсор влево
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
// Взвращает индекс в массиве пропусков,если координаты совпадают с одним из элементов, если нет, то возвращает -1
int find_marked(ITEM pos,int ** marked,int hide){
    for(int i = 0;i<hide;i++){
        if(pos.column == *(*(marked+i)+1) && pos.row == **(marked+i)) return i;
    }
    return -1;
}
// Функция ручного решения судоку
void game(int ** sudoku, int mode, int hide) {
    // Вывод судоку и элементов управления
    print_sudoku(sudoku,mode);
    printf("\"e\" - to enter, \"q\" - to quit, \"wasd\" - to move");
    // Обьявление ключевых переменных
    int solved[hide], count = 0; // Счётчик решенных пропусков
    ITEM pos = generate_item(-1,0,0,mode); // Текущий элемент судоку
    set_to_point(pos); // Перемещение курсора на 1 элемент
    for(int i = 0; i<hide;i++) {
        *(solved+i) = 0;
    }
    char c; // переменная для хранения введенного символа
    int end = 0; // флаг принудительного завершения программы
    int ** marked = get_positions(sudoku,mode,hide); // создание массива координат пропусков
    
    int changed = 0; // флаг была ли изменена текущая ячейка
    while(count<hide){
        c = getch();
        // выбор того, какое действие будет произведено
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
        if(c-'0' <= mode) pos.value = c-'0'; // проверка значения на соответствие размерности
        else pos.value = 0;
        printf("Current: %d",pos.value);
        default:
            break;
        }
        // Проверка текущего состояния судоку (насколько решена)
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
        //принудительное завершение
        if(end == 1) break;
        
    }
    // перевод каретки на конец
    set_to_end(mode);
    // вывод результата
    if(end == 1) printf("Maybe next time(");
    else printf("You won!!!");
    // освобождение вспомогательного массива
    free_matrix(marked,hide);
}
#endif
