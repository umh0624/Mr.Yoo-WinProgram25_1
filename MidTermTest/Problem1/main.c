#include <stdio.h>

// 함수 선언
int PassOrFail(int score);

// main 함수
int main() {
    int myScore = 45;  // 본인의 예상 점수

    int result = PassOrFail(myScore);

    if (result == 1)
        printf("재시험 없습니다!\n");
    else
        printf("우리는 망했다… 재시험이다…\n");

    return 0;
}

// PassOrFail 함수 정의
int PassOrFail(int score) {
    if (score >= 50)
        return 1;
    else
        return 0;
}
