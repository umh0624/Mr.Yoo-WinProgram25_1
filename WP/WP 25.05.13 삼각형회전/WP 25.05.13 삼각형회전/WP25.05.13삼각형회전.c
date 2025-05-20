#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>

// ���� ȸ�� ����
float angle = 0.0f;

// �ﰢ�� �׸��� �Լ� (���� + ��ǥ)
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

    GLFWwindow* window = glfwCreateWindow(500, 500, "GLFW: ȸ���ϴ� �ﰢ��", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // ���� �ð� �����
    float prevTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // ���� �ð� Ȯ��
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - prevTime;
        prevTime = currentTime;

        // 1�ʿ� �� ���� ȸ�� (360��/��)
        angle += 90.0f * deltaTime; // �ʴ� 90�� ȸ��
        if (angle >= 360.0f) angle -= 360.0f;

        glPushMatrix();                  // ���� ��� ����
        glRotatef(angle, 0.0f, 0.0f, 1.0f); // Z�� �߽� ȸ��
        draw_triangle();                // ȸ�� ����� �ﰢ�� �׸���
        glPopMatrix();                  // ���� ��� ����

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
