#include <windows.h>
#include <stdio.h>

void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

int main() {
    system("cls");
    SetConsoleOutputCP(65001); // UTF-8 설정
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int width = 80;
    int height = 25;

    for (int y = 1; y < height; y++) {  // 위쪽 1줄 제외
        move_cursor(y + 1, 3);  // 콘솔은 1부터 시작하므로 +1 보정, 좌측 여백 2칸 → col = 3
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
        for (int x = 0; x < width - 4; x++) {  // 좌우 2칸씩 → 총 4칸 제외
            printf(" ");
        }
        SetConsoleTextAttribute(hConsole, 7); // 색상 초기화
    }

    move_cursor(26, 1); // 커서 맨 밑으로
    return 0;
}
