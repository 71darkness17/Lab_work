#include<stdio.h>
int main() {
    char c;
    switch(c = getchar()){
        case 'a': case'A':
            puts("b");
    }
    return 0;
}