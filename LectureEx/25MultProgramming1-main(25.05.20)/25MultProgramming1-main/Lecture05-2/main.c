#include <Windows.h>
#include <stdio.h>

void gotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int main() {
    gotoXY(10, 10);

    // ������ �ؽ�Ʈ
    printf("\033[31m�� �ؽ�Ʈ�� �������Դϴ�.\033[0m\n");

    // �ʷϻ� �ؽ�Ʈ�� ����� ���
    printf("\033[32m\033[43m�� �ؽ�Ʈ�� �ʷϻ��̰� ����� ������Դϴ�.\033[0m\n");

    // ���� �ؽ�Ʈ�� �Ķ��� �ؽ�Ʈ
    printf("\033[1m\033[34m�� �ؽ�Ʈ�� ���� �Ķ����Դϴ�.\033[0m\n");

    return 0;
}

