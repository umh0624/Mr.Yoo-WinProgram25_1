#include <windows.h>   // 콘솔 화면 조작, 핸들 사용, 커서 이동 등 Windows API 제공
#include <stdio.h>     // 기본 입출력 함수 (printf, getchar 등)

// 콘솔 커서를 (x, y) 위치로 이동시키는 함수.
// 콘솔에서 원하는 위치에 출력하려면 커서를 직접 이동시켜야 함.
// 이를 통해 화면을 GUI처럼 구성할 수 있게 됨.
void gotoxy(int x, int y)
{
    COORD pos = { x, y };  // (x, y) 좌표를 저장할 구조체 생성
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    // 콘솔 핸들을 얻고, 해당 위치로 커서 이동
}

// ANSI Escape Code 기능을 활성화하는 함수.
// 기본 Windows CMD는 ANSI 코드(색상, 커서 이동 등)를 지원하지 않음.
// Windows 10 이상에서는 이 플래그를 켜야 ANSI 스타일이 적용됨.
void enableAnsi()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  // 콘솔 출력 핸들 얻기
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);                  // 현재 콘솔 모드 읽기
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;   // ANSI 지원 기능 플래그 추가
    SetConsoleMode(hOut, dwMode);                   // 변경된 모드를 다시 설정
}

// 콘솔 전체를 초록색 배경으로 칠하는 함수.
// \033[42m 은 ANSI 코드에서 초록색 배경을 의미함.
// 콘솔 라인 수만큼 반복하며 한 줄씩 채워줌.
void fillGreenBackground()
{
    for (int i = 0; i < 60; i++) {
        printf("\033[42m%*s\033[0m\n", 120, "");
        // 너비 120만큼 공백을 출력하고, 초록색 배경으로 채움
    }
}

// 윈도우 창의 속성을 정의하는 구조체.
// x, y : 창 위치 좌표, width, height : 창의 크기
// name : 윈도우 상단바에 표시될 이름
// color : 창의 배경색 (ANSI 코드 형태로 저장)
typedef struct {
    int x;
    int y;
    int width;
    int height;
    char name[30];
    char color[8];  // 예: "\033[43m" (노란 배경)
} WinPro25;

// 구조체에 저장된 정보를 기반으로 실제 콘솔에 창을 그리는 함수.
// 테두리, 제목, 종료 버튼, 내부 배경까지 포함해서 출력함.
void drawWindow(WinPro25 win)
{
    // (1) 전체 창 영역을 지정된 배경색으로 채우기
    for (int i = 0; i < win.height; i++) {
        gotoxy(win.x, win.y + i);  // 각 행마다 커서 이동
        printf("%s", win.color);   // 배경 색상 설정
        for (int j = 0; j < win.width; j++) printf(" ");
        printf("\033[0m");         // 색상 초기화
    }

    // (2) 윗 테두리 그리기: ┌───┐ 모양
    gotoxy(win.x, win.y);
    printf("\033[30m%s┌", win.color);  // 검정색 글자 + 배경색
    for (int i = 0; i < win.width - 2; i++) printf("─");
    printf("┐\033[0m");

    // (3) 아랫 테두리 그리기: └───┘
    gotoxy(win.x, win.y + win.height - 1);
    printf("\033[30m%s└", win.color);
    for (int i = 0; i < win.width - 2; i++) printf("─");
    printf("┘\033[0m");

    // (4) 좌우 세로 테두리 그리기
    for (int i = 1; i < win.height - 1; i++) {
        gotoxy(win.x, win.y + i);
        printf("\033[30m%s│\033[0m", win.color);  // 왼쪽 테두리
        gotoxy(win.x + win.width - 1, win.y + i);
        printf("\033[30m%s│\033[0m", win.color);  // 오른쪽 테두리
    }

    // (5) 상단바와 본문 사이 구분선 (─)
    gotoxy(win.x + 1, win.y + 2);
    printf("\033[30m%s", win.color);
    for (int i = 0; i < win.width - 2; i++) printf("─");
    printf("\033[0m");

    // (6) 창 제목 출력
    gotoxy(win.x + 2, win.y + 1);
    printf("\033[30m%s%s\033[0m", win.color, win.name);

    // (7) 종료 버튼 출력 (오른쪽 상단)
    gotoxy(win.x + win.width - 6, win.y + 1);
    printf("\033[30m%s[×]\033[0m", win.color);
}

int main()
{
    system("mode con cols=120 lines=60");  // 콘솔 크기를 120x60으로 설정
    system("cls");                          // 이전 콘솔 내용 모두 지우기

    enableAnsi();           // ANSI Escape Code 사용 가능하게 만들기
    fillGreenBackground();  // 전체 배경을 초록색으로 채움

    for (int i = 0; i < 3; i++) printf("\n");  // 아래 출력 겹침 방지용 여백

    // 첫 번째 창 정보 (조건: 20x7, 위치 (10,3), 노란색)
    WinPro25 win1 = { 10, 3, 20, 7, "Window 1", "\033[43m" };

    // 두 번째 창 정보 (조건: 20x7, 위치 (15,5), 청록색)
    WinPro25 win2 = { 15, 5, 20, 7, "Window 2", "\033[46m" };

    drawWindow(win1);  // 첫 번째 창 출력
    drawWindow(win2);  // 두 번째 창 출력

    gotoxy(0, 58);     // 커서를 맨 아래로 내려 디버깅 메시지 겹침 방지
    printf("\033[0m"); // 모든 색상 스타일 초기화
    getchar();         // 프로그램 종료 대기 (엔터 입력 기다림)

    return 0;
}
