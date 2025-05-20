#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>

//Nuget ��Ű�� �Ŵ������� GLFW ��ġ �� ���

void draw_triangle() {

    glBegin(GL_TRIANGLES);
    glColor3f(2.0f, 0.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    glColor3f(0.0f, 2.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 2.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: �ﰢ��", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_triangle();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}