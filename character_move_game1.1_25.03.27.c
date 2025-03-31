#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void menu() {
    puts("天天0天天");
}
//20231384 嶸團⑶
void main() {
    menu();
    int i = 2;
    char move;

    while (i >= 0 && i < 5) {
        move = _getch();

        if (move == 'a') {
            if (i > 0) {
                i--;
            }
        }
        else if (move == 'd') {
            if (i < 4) {
                i++;
            }
        }

        system("cls");
        int j;

        for (j = 0; j < 5; j++) {
            if (j == i)
                printf("0");
            else
                printf("天");
        }
        printf("\n");
    }
}