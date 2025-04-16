#include <windows.h>   // �ܼ� ȭ�� ����, �ڵ� ���, Ŀ�� �̵� �� Windows API ����
#include <stdio.h>     // �⺻ ����� �Լ� (printf, getchar ��)

// �ܼ� Ŀ���� (x, y) ��ġ�� �̵���Ű�� �Լ�.
// �ֿܼ��� ���ϴ� ��ġ�� ����Ϸ��� Ŀ���� ���� �̵����Ѿ� ��.
// �̸� ���� ȭ���� GUIó�� ������ �� �ְ� ��.
void gotoxy(int x, int y)
{
    COORD pos = { x, y };  // (x, y) ��ǥ�� ������ ����ü ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    // �ܼ� �ڵ��� ���, �ش� ��ġ�� Ŀ�� �̵�
}

// ANSI Escape Code ����� Ȱ��ȭ�ϴ� �Լ�.
// �⺻ Windows CMD�� ANSI �ڵ�(����, Ŀ�� �̵� ��)�� �������� ����.
// Windows 10 �̻󿡼��� �� �÷��׸� �Ѿ� ANSI ��Ÿ���� �����.
void enableAnsi()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  // �ܼ� ��� �ڵ� ���
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);                  // ���� �ܼ� ��� �б�
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;   // ANSI ���� ��� �÷��� �߰�
    SetConsoleMode(hOut, dwMode);                   // ����� ��带 �ٽ� ����
}

// �ܼ� ��ü�� �ʷϻ� ������� ĥ�ϴ� �Լ�.
// \033[42m �� ANSI �ڵ忡�� �ʷϻ� ����� �ǹ���.
// �ܼ� ���� ����ŭ �ݺ��ϸ� �� �پ� ä����.
void fillGreenBackground()
{
    for (int i = 0; i < 60; i++) {
        printf("\033[42m%*s\033[0m\n", 120, "");
        // �ʺ� 120��ŭ ������ ����ϰ�, �ʷϻ� ������� ä��
    }
}

// ������ â�� �Ӽ��� �����ϴ� ����ü.
// x, y : â ��ġ ��ǥ, width, height : â�� ũ��
// name : ������ ��ܹٿ� ǥ�õ� �̸�
// color : â�� ���� (ANSI �ڵ� ���·� ����)
typedef struct {
    int x;
    int y;
    int width;
    int height;
    char name[30];
    char color[8];  // ��: "\033[43m" (��� ���)
} WinPro25;

// ����ü�� ����� ������ ������� ���� �ֿܼ� â�� �׸��� �Լ�.
// �׵θ�, ����, ���� ��ư, ���� ������ �����ؼ� �����.
void drawWindow(WinPro25 win)
{
    // (1) ��ü â ������ ������ �������� ä���
    for (int i = 0; i < win.height; i++) {
        gotoxy(win.x, win.y + i);  // �� �ึ�� Ŀ�� �̵�
        printf("%s", win.color);   // ��� ���� ����
        for (int j = 0; j < win.width; j++) printf(" ");
        printf("\033[0m");         // ���� �ʱ�ȭ
    }

    // (2) �� �׵θ� �׸���: ���������� ���
    gotoxy(win.x, win.y);
    printf("\033[30m%s��", win.color);  // ������ ���� + ����
    for (int i = 0; i < win.width - 2; i++) printf("��");
    printf("��\033[0m");

    // (3) �Ʒ� �׵θ� �׸���: ����������
    gotoxy(win.x, win.y + win.height - 1);
    printf("\033[30m%s��", win.color);
    for (int i = 0; i < win.width - 2; i++) printf("��");
    printf("��\033[0m");

    // (4) �¿� ���� �׵θ� �׸���
    for (int i = 1; i < win.height - 1; i++) {
        gotoxy(win.x, win.y + i);
        printf("\033[30m%s��\033[0m", win.color);  // ���� �׵θ�
        gotoxy(win.x + win.width - 1, win.y + i);
        printf("\033[30m%s��\033[0m", win.color);  // ������ �׵θ�
    }

    // (5) ��ܹٿ� ���� ���� ���м� (��)
    gotoxy(win.x + 1, win.y + 2);
    printf("\033[30m%s", win.color);
    for (int i = 0; i < win.width - 2; i++) printf("��");
    printf("\033[0m");

    // (6) â ���� ���
    gotoxy(win.x + 2, win.y + 1);
    printf("\033[30m%s%s\033[0m", win.color, win.name);

    // (7) ���� ��ư ��� (������ ���)
    gotoxy(win.x + win.width - 6, win.y + 1);
    printf("\033[30m%s[��]\033[0m", win.color);
}

int main()
{
    system("mode con cols=120 lines=60");  // �ܼ� ũ�⸦ 120x60���� ����
    system("cls");                          // ���� �ܼ� ���� ��� �����

    enableAnsi();           // ANSI Escape Code ��� �����ϰ� �����
    fillGreenBackground();  // ��ü ����� �ʷϻ����� ä��

    for (int i = 0; i < 3; i++) printf("\n");  // �Ʒ� ��� ��ħ ������ ����

    // ù ��° â ���� (����: 20x7, ��ġ (10,3), �����)
    WinPro25 win1 = { 10, 3, 20, 7, "Window 1", "\033[43m" };

    // �� ��° â ���� (����: 20x7, ��ġ (15,5), û�ϻ�)
    WinPro25 win2 = { 15, 5, 20, 7, "Window 2", "\033[46m" };

    drawWindow(win1);  // ù ��° â ���
    drawWindow(win2);  // �� ��° â ���

    gotoxy(0, 58);     // Ŀ���� �� �Ʒ��� ���� ����� �޽��� ��ħ ����
    printf("\033[0m"); // ��� ���� ��Ÿ�� �ʱ�ȭ
    getchar();         // ���α׷� ���� ��� (���� �Է� ��ٸ�)

    return 0;
}
