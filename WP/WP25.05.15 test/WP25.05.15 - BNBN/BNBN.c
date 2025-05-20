#include <GLFW/glfw3.h>
#include <math.h>
#pragma comment(lib, "Opengl32.lib")
#define PI 3.1415926535f

void draw_blue_circle() {
    int segments = 100;
    float radius = 0.5f;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < segments; i++) {
        float angle1 = 2.0f * PI * i / segments;
        float angle2 = 2.0f * PI * (i + 1) / segments;

        float x1 = radius * cosf(angle1);
        float y1 = radius * sinf(angle1);
        float x2 = radius * cosf(angle2);
        float y2 = radius * sinf(angle2);

        glColor3f(0.0f, 0.0f, 1.0f); // 파란색
        glVertex2f(0.0f, 0.0f);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(537, 445, "파란 원 출력", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 배경: 흰색

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_blue_circle();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
