#include <windows.h>
#include <stdio.h>

int main() {
    char letter = 'O';
    POINT mousePos;
    int isDragging = 0;
    int letterX = 10, letterY = 5;

    HWND hwnd = GetConsoleWindow();
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFO font;
    GetCurrentConsoleFont(hOut, FALSE, &font);

    int charWidth = font.dwFontSize.X > 0 ? font.dwFontSize.X : 8;
    int charHeight = font.dwFontSize.Y > 0 ? font.dwFontSize.Y : 16;

    RECT clientRect;
    GetClientRect(hwnd, &clientRect);

    POINT origin = { 0, 0 };
    ClientToScreen(hwnd, &origin);

    while (1) {
        GetCursorPos(&mousePos);
        int relX = mousePos.x - origin.x - 130;
        int relY = mousePos.y - origin.y - 120;

        int cursorX = relX / charWidth;
        int cursorY = relY / charHeight;

        SHORT leftDown = GetAsyncKeyState(VK_LBUTTON) & 0x8000;
        if (leftDown && cursorX == letterX && cursorY == letterY) {
            isDragging = 1;
        }
        else if (!leftDown) {
            isDragging = 0;
        }

        if (isDragging) {
            letterX = cursorX;
            letterY = cursorY;
        }

        system("cls");
        printf("알파벳 '%c'을 마우스로 드래그하세요.\n", letter);
        printf("현재 알파벳 '%c'의 위치: (%d, %d)\n\n", letter, letterX, letterY);

        // 종료 조건: Q 또는 ESC 키를 누르면 종료
        if (GetAsyncKeyState('Q') & 0x8000 || GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            printf("\n프로그램 종료\n");
            break;
        }

        COORD cursorPos = { (SHORT)cursorX, (SHORT)cursorY };
        SetConsoleCursorPosition(hOut, cursorPos);
        printf("<");

        COORD letterPos = { (SHORT)letterX, (SHORT)letterY };
        SetConsoleCursorPosition(hOut, letterPos);
        printf("%c", letter);

        Sleep(100);
    }

    return 0;
}
