#include <GLFW/glfw3.h>
#include <math.h>
#pragma comment(lib, "Opengl32.lib")
#define PI 3.1415926535f

typedef struct { float x, y; } Vec2;

typedef struct {
    Vec2 position;
    float rotation;
    Vec2 scale;
} Transform;

typedef struct {
    float r, g, b;
} Color;

typedef struct {
    Transform transform;
    int segments;
    Color color;
} Circle;

void draw_circle(Circle* c) {
    glPushMatrix();
    glTranslatef(c->transform.position.x, c->transform.position.y, 0.0f);
    glRotatef(c->transform.rotation * (180.0f / PI), 0.0f, 0.0f, 1.0f);
    glScalef(c->transform.scale.x, c->transform.scale.y, 1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(c->color.r, c->color.g, c->color.b);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= c->segments; ++i) {
        float angle = 2.0f * PI * i / c->segments;
        glVertex2f(cosf(angle) * 0.5f, sinf(angle) * 0.5f);
    }
    glEnd();

    glPopMatrix();
}

void draw_line(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(537, 445, "보노보노 얼굴", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glOrtho(-1, 1, -1, 1, -1, 1); // 2D 좌표계 설정

    // 얼굴 테두리라인
    Circle outline = { {{0, 0}, 0, {405 / 800.0f * 2, 385 / 600.0f * 2 * 0.85f}}, 100, {0.0f, 0.0f, 0.0f} };

    // 얼굴
    Circle face = { {{0, 0}, 0, {400 / 800.0f * 2, 380 / 600.0f * 2 * 0.85f}}, 100, {0.0f, 0.4392f, 0.7490f} };

    // 눈깔
    Circle eyeLeft = { {{-150 / 800.0f * 2, 50 / 600.0f * 2}, 0, {30 / 800.0f * 2, 30 / 600.0f * 2}}, 100, {0.0f, 0.0f, 0.0f} };
    Circle eyeRight = { {{150 / 800.0f * 2, 50 / 600.0f * 2}, 0, {30 / 800.0f * 2, 30 / 600.0f * 2}}, 100, {0.0f, 0.0f, 0.0f} };

    // 코
    Circle nose = { {{0, -25 / 600.0f * 2}, 0, {60 / 800.0f * 2, 60 / 600.0f * 2 * 0.7f}}, 100, {0.0f, 0.0f, 0.0f} };

    // 하얀색주둥이
    Circle mouthLeft = { {{40 / 800.0f * 2, -60 / 600.0f * 2}, 0, {90 / 800.0f * 2, 75 / 600.0f * 2 * 0.85f}}, 100, {1.0f, 1.0f, 1.0f} };
    Circle mouthRight = { {{-40 / 800.0f * 2, -60 / 600.0f * 2}, 0, {90 / 800.0f * 2, 75 / 600.0f * 2 * 0.85f}}, 100, {1.0f, 1.0f, 1.0f} };

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 흰색 배경이 나오게하기~

        draw_circle(&outline);
        draw_circle(&face);
        draw_circle(&eyeLeft);
        draw_circle(&eyeRight);
        draw_circle(&mouthLeft);
        draw_circle(&mouthRight);
        draw_circle(&nose);

        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);  // 수염을 좀 더 두껍게 하기 위해 선의 width를 조정해줬음

        draw_line(45 / 800.0f * 2, -60 / 600.0f * 2, 115 / 800.0f * 2, -60 / 600.0f * 2);
        draw_line(45 / 800.0f * 2, -40 / 600.0f * 2, 115 / 800.0f * 2, -20 / 600.0f * 2);
        draw_line(45 / 800.0f * 2, -80 / 600.0f * 2, 115 / 800.0f * 2, -100 / 600.0f * 2);

        draw_line(-45 / 800.0f * 2, -60 / 600.0f * 2, -115 / 800.0f * 2, -60 / 600.0f * 2);
        draw_line(-45 / 800.0f * 2, -40 / 600.0f * 2, -115 / 800.0f * 2, -20 / 600.0f * 2);
        draw_line(-45 / 800.0f * 2, -80 / 600.0f * 2, -115 / 800.0f * 2, -100 / 600.0f * 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
