#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>

// 현재 회전 각도
float angle = 0.0f;

// 삼각형 그리기 함수 (색상 + 좌표)
void draw_triangle() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.5f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: 회전하는 삼각형", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // 이전 시간 저장용
    float prevTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // 현재 시간 확인
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - prevTime;
        prevTime = currentTime;

        // 1초에 한 바퀴 회전 (360도/초)
        angle += 90.0f * deltaTime; // 초당 90도 회전
        if (angle >= 360.0f) angle -= 360.0f;

        glPushMatrix();                  // 이전 행렬 저장
        glRotatef(angle, 0.0f, 0.0f, 1.0f); // Z축 중심 회전
        draw_triangle();                // 회전 적용된 삼각형 그리기
        glPopMatrix();                  // 원래 행렬 복원

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
