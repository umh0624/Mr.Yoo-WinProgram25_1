#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void menu() {
    puts("�Ѥ�0�Ѥ�");
}
//20231384 ������
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
                printf("��");
        }
        printf("\n");
    }
}