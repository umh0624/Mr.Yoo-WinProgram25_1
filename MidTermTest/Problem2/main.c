#include <stdio.h>
#include <windows.h>

void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col);
}

void set_color(int text, int bg) {
    printf("\033[3%d;4%dm", text, bg);
}

void reset_color() {
    printf("\033[0m");
}

// 파란색 바탕화면 그리기
void drawBackground() {
    int width = 80, height = 25;
    int leftMargin = 2;
    int topMargin = 1;

    set_color(0, 4);  // 검정 글자, 파란 배경

    for (int y = topMargin + 1; y <= height - 1; y++) {  // 작업표시줄 1칸 제외
        move_cursor(y, leftMargin + 1);
        for (int x = 0; x < width - leftMargin * 2; x++) {
            printf(" ");
        }
    }

    reset_color();
}

// 작업 표시줄 (흰색, 1칸) 그리기
void drawTaskbar() {
    int width = 80;
    int height = 25;
    int leftMargin = 2;
    int taskbarY = height; // 가장 하단

    set_color(0, 7);  // 검정 글자, 흰색 배경
    move_cursor(taskbarY, leftMargin + 1);
    for (int x = 0; x < width - leftMargin * 2; x++) {
        printf(" ");
    }
    reset_color();
}

// 콘솔 윈도우 그리기
void drawConsoleWindow(int startX, int startY, int width, int height, const char* title, int color) {
    set_color(7, color);  // 흰 글자, 배경색

    for (int y = 0; y < height; y++) {
        move_cursor(startY + y, startX);
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height - 1) {
                printf("-");
            }
            else if (x == 0 || x == width - 1) {
                printf("|");
            }
            else {
                printf(" ");
            }
        }
    }

    // 제목
    move_cursor(startY, startX + 2);
    printf("%s", title);

    // X 버튼
    set_color(7, 1);  // 흰 글자, 빨간 배경
    move_cursor(startY, startX + width - 4);
    printf(" X ");
    reset_color();
}

int main() {
    system("cls");

    drawBackground();        // 파란 배경 먼저 그리기
    drawTaskbar();           // 하단 작업표시줄 추가

    // 윈도우 1: cyan
    drawConsoleWindow(5, 3, 30, 10, "Cyan Window", 6);      // Cyan (color 6)

    // 윈도우 2: magenta
    drawConsoleWindow(25, 8, 30, 10, "Magenta Window", 5);  // Magenta (color 5)

    // 윈도우 3: brown
    drawConsoleWindow(45, 5, 30, 12, "Brown Window", 3);    // Brown (color 3)

    move_cursor(26, 1);  // 커서 아래로 내리기
    return 0;
}
