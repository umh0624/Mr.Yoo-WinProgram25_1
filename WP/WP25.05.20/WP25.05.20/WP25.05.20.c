#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>
#pragma comment(lib, "Opengl32.lib")
#define PI 3.1415926535f

// ─── 원 그리기
void drawCircle(float cx, float cy, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float a = 2.0f * PI * i / segments;
        glVertex2f(cx + cosf(a) * radius, cy + sinf(a) * radius);
    }
    glEnd();
}

// ─── 외부 시계: 60분 눈금 (5분마다 굵은 눈금)
void drawOuterTicks(float radius) {
    for (int i = 0; i < 60; i++) {
        float a = 2.0f * PI * i / 60.0f;
        float inner = (i % 5 == 0) ? radius * 0.9f : radius * 0.95f;
        float outer = radius;
        glLineWidth((i % 5 == 0) ? 3.0f : 1.0f);
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(cosf(a) * inner, sinf(a) * inner);
        glVertex2f(cosf(a) * outer, sinf(a) * outer);
        glEnd();
    }
}

// ─── 내부 시계: 60초 눈금 (5초마다 굵은 눈금)
void drawInnerSecTicks(float cx, float cy, float radius) {
    glPushMatrix();
    glTranslatef(cx, cy, 0);
    for (int i = 0; i < 60; i++) {
        float a = 2.0f * PI * i / 60.0f;
        float inner = (i % 5 == 0) ? radius * 0.85f : radius * 0.90f;
        float outer = radius;
        glLineWidth((i % 5 == 0) ? 2.0f : 1.0f);
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(cosf(a) * inner, sinf(a) * inner);
        glVertex2f(cosf(a) * outer, sinf(a) * outer);
        glEnd();
    }
    glPopMatrix();
}

// ─── 바늘 그리기 (+삼각형 옵션)
void drawHand(float angle, float length, float width,
    float r, float g, float b,
    int hasTri, float triSize,
    float tr, float tg, float tb)
{
    glPushMatrix();
    glRotatef(angle, 0, 0, 1);

    // 바늘 본체
    glColor3f(r, g, b);
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, length);
    glEnd();

    // 끝 삼각형
    if (hasTri) {
        glColor3f(tr, tg, tb);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, length + triSize);
        glVertex2f(-triSize, length);
        glVertex2f(triSize, length);
        glEnd();
    }
    glPopMatrix();
}

// ─── 현재 시각 → 바늘 각도 계산
void getCurrentTime(float* hA, float* mA, float* sA) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    *sA = -(t->tm_sec * 6.0f);
    *mA = -(t->tm_min * 6.0f + t->tm_sec * 0.1f);
    *hA = -((t->tm_hour % 12) * 30.0f + t->tm_min * 0.5f);
}
 
int main() {
    if (!glfwInit()) return -1;
    GLFWwindow* w = glfwCreateWindow(600, 600, "Dual Clock", NULL, NULL);
    if (!w) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(w);
    glOrtho(-1, 1, -1, 1, -1, 1);

    const float outerR = 0.8f;
    const float innerCX = -0.4f, innerCY = 0.0f;
    const float innerR = outerR * 0.25f;

    float hAngle, mAngle, sAngle;
    while (!glfwWindowShouldClose(w)) {
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // 1) 외부 시계 배경 & 분 눈금
        drawCircle(0, 0, outerR, 100);
        drawOuterTicks(outerR);

        // 2) 내부 시계 배경 & 초 눈금
        drawCircle(innerCX, innerCY, innerR, 60);
        drawInnerSecTicks(innerCX, innerCY, innerR);

        // 3) 현재 시간 계산
        getCurrentTime(&hAngle, &mAngle, &sAngle);

        // 4) 내부 시계 초침 (빨강 + 작은 삼각형)
        glPushMatrix();
        glTranslatef(innerCX, innerCY, 0);
        drawHand(sAngle, innerR * 0.8f, 2.0f,
            1, 0, 0, 1, innerR * 0.1f, 1, 0, 0);
        glPopMatrix();

        // 5) 외부 시계 시침·분침 (검정 + 삼각형) → 가장 위에 그려짐
        drawHand(hAngle, outerR * 0.5f, 5.0f,
            0, 0, 0, 1, 0.03f, 0, 0, 0);
        drawHand(mAngle, outerR * 0.75f, 3.0f,
            0, 0, 0, 1, 0.03f, 0, 0, 0);

        glfwSwapBuffers(w);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
