#pragma comment(lib, "Opengl32.lib") // OpenGL 라이브러리를 링커에 포함시킴

#include <GLFW/glfw3.h> // GLFW 사용을 위한 헤더
#include <cmath>        // 삼각함수 사용을 위한 수학 라이브러리

#define PI 3.14159265358979323846 // 원주율 정의 (π)

// 🔺 삼각형들을 조합해서 원처럼 보이게 만드는 함수
void draw_triangle() {
    const int segments = 300;   // 삼각형 개수 (많을수록 원이 매끄러워짐)
    const float radius = 0.5f;  // 원의 반지름 (OpenGL 좌표계는 -1.0 ~ 1.0 사이)

    glBegin(GL_TRIANGLES);      // 삼각형 그리기 시작
    for (int i = 0; i < segments; ++i) {
        // 현재 삼각형의 두 외곽 꼭짓점 각도 계산
        float angle1 = 2.0f * PI * i / segments;
        float angle2 = 2.0f * PI * (i + 1) / segments;

        // 각 꼭짓점의 위치 계산
        float x1 = radius * cosf(angle1);
        float y1 = radius * sinf(angle1);
        float x2 = radius * cosf(angle2);
        float y2 = radius * sinf(angle2);

        // 🟥 중심점 (고정): 빨간색
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f); // 중심 좌표 (0,0)

        // 🟩 첫 번째 꼭짓점 (외곽): 초록-파랑 혼합 색상
        glColor3f(0.0f, (float)i / segments, 1.0f - (float)i / segments);
        glVertex2f(x1, y1);

        // 🟦 두 번째 꼭짓점 (외곽): 파랑-초록 혼합 색상
        glColor3f(0.0f, (float)(i + 1) / segments, 1.0f - (float)(i + 1) / segments);
        glVertex2f(x2, y2);
    }
    glEnd(); // 그리기 끝
}

int main() {
    // GLFW 초기화
    if (!glfwInit()) return -1;

    // 윈도우 생성 (너비 500, 높이 500, 제목)
    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: 매끄러운 원", NULL, NULL);
    if (!window) {
        glfwTerminate(); // 실패 시 종료
        return -1;
    }

    // 생성한 윈도우를 현재 OpenGL 컨텍스트로 설정
    glfwMakeContextCurrent(window);

    // 배경색 설정: 검정 (RGBA)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // 메인 루프: 윈도우가 닫힐 때까지 반복
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT); // 화면 초기화

        draw_triangle(); // 원 그리기 함수 호출

        glfwSwapBuffers(window); // 버퍼 교체 (화면에 출력)
        glfwPollEvents();        // 입력/이벤트 처리
    }

    // 리소스 정리 및 종료
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
