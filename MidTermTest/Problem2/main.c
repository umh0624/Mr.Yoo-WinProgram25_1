#include <windows.h>
#include <stdio.h>

void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

int main() {
    system("cls");
    SetConsoleOutputCP(65001); // UTF-8 ����
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int width = 80;
    int height = 25;

    for (int y = 1; y < height; y++) {  // ���� 1�� ����
        move_cursor(y + 1, 3);  // �ܼ��� 1���� �����ϹǷ� +1 ����, ���� ���� 2ĭ �� col = 3
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
        for (int x = 0; x < width - 4; x++) {  // �¿� 2ĭ�� �� �� 4ĭ ����
            printf(" ");
        }
        SetConsoleTextAttribute(hConsole, 7); // ���� �ʱ�ȭ
    }

    move_cursor(26, 1); // Ŀ�� �� ������
    return 0;
}
