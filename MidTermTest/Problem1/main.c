#include <stdio.h>

// �Լ� ����
int PassOrFail(int score);

// main �Լ�
int main() {
    int myScore = 45;  // ������ ���� ����

    int result = PassOrFail(myScore);

    if (result == 1)
        printf("����� �����ϴ�!\n");
    else
        printf("�츮�� ���ߴ١� ������̴١�\n");

    return 0;
}

// PassOrFail �Լ� ����
int PassOrFail(int score) {
    if (score >= 50)
        return 1;
    else
        return 0;
}
