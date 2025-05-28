#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>
#pragma comment(lib, "Opengl32.lib")
#define PI 3.1415926535f

// 원 그리기 (흰색 배경)
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

// 외부 시계 눈금
void drawOuterTicks(float radius) {
    for (int i = 0; i < 60; i++) {
        float a = 2.0f * PI * i / 60.0f;
        float inner = (i % 5 == 0) ? radius * 0.9f : radius * 0.95f;
        glLineWidth((i % 5 == 0) ? 3.0f : 1.0f);
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(cosf(a) * inner, sinf(a) * inner);
        glVertex2f(cosf(a) * radius, sinf(a) * radius);
        glEnd();
    }
}

// 내부 시계 눈금 (초)
void drawInnerSecTicks(float cx, float cy, float radius) {
    glPushMatrix();
    glTranslatef(cx, cy, 0);
    for (int i = 0; i < 60; i++) {
        float a = 2.0f * PI * i / 60.0f;
        float inner = (i % 5 == 0) ? radius * 0.85f : radius * 0.90f;
        glLineWidth((i % 5 == 0) ? 2.0f : 1.0f);
        glColor3f(0, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(cosf(a) * inner, sinf(a) * inner);
        glVertex2f(cosf(a) * radius, sinf(a) * radius);
        glEnd();
    }
    glPopMatrix();
}

// 바늘 그리기 (삼각형 끝 추가)
void drawHand(float angle, float length, float width, float r, float g, float b, int hasTri, float triSize) {
    glPushMatrix();
    glRotatef(angle, 0, 0, 1);
    glColor3f(r, g, b);
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(0, length);
    glEnd();

    if (hasTri) {
        glBegin(GL_TRIANGLES);
        glVertex2f(0, length + triSize);
        glVertex2f(-triSize, length);
        glVertex2f(triSize, length);
        glEnd();
    }
    glPopMatrix();
}

// 현재 시각 얻기
void getCurrentTime(float* hA, float* mA, float* sA) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    *sA = -(t->tm_sec * 6.0f);
    *mA = -(t->tm_min * 6.0f + t->tm_sec * 0.1f);
    *hA = -((t->tm_hour % 12) * 30.0f + t->tm_min * 0.5f);
}

// 디지털 숫자 세그먼트
int segments[10] = { 0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x7B };

// 디지털 숫자 그리기
void drawDigit(float x, float y, float w, float h, int num) {
    glColor3f(1, 0, 0); glLineWidth(3);
    float hw = w / 2, hh = h / 2;
    int seg = segments[num];
    glBegin(GL_LINES);
    if (seg & 0x40) { glVertex2f(x - hw, y + hh); glVertex2f(x + hw, y + hh); }
    if (seg & 0x20) { glVertex2f(x + hw, y + hh); glVertex2f(x + hw, y); }
    if (seg & 0x10) { glVertex2f(x + hw, y); glVertex2f(x + hw, y - hh); }
    if (seg & 0x08) { glVertex2f(x + hw, y - hh); glVertex2f(x - hw, y - hh); }
    if (seg & 0x04) { glVertex2f(x - hw, y - hh); glVertex2f(x - hw, y); }
    if (seg & 0x02) { glVertex2f(x - hw, y); glVertex2f(x - hw, y + hh); }
    if (seg & 0x01) { glVertex2f(x - hw, y); glVertex2f(x + hw, y); }
    glEnd();
}

// 콜론 그리기
void drawColon(float x, float y, float size) {
    glColor3f(1, 0, 0); glPointSize(6);
    glBegin(GL_POINTS);
    glVertex2f(x, y + size); glVertex2f(x, y - size);
    glEnd();
}

int main() {
    glfwInit();
    GLFWwindow* w = glfwCreateWindow(600, 600, "Clock", 0, 0);
    glfwMakeContextCurrent(w);
    glOrtho(-1, 1, -1, 1, -1, 1);

    float outerR = 0.8f, innerCX = -0.4f, innerCY = 0, innerR = 0.2f;
    float hA, mA, sA;

    while (!glfwWindowShouldClose(w)) {
        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        drawCircle(0, 0, outerR, 100);
        drawOuterTicks(outerR);
        drawCircle(innerCX, innerCY, innerR, 60);
        drawInnerSecTicks(innerCX, innerCY, innerR);

        getCurrentTime(&hA, &mA, &sA);

        // 디지털 시계(검정 배경)
        float dw = 0.5f, dh = 0.13f, dx = 0, dy = -0.43f;
        glColor3f(0, 0, 0);
        glBegin(GL_QUADS);
        glVertex2f(dx - dw, dy - dh); glVertex2f(dx + dw, dy - dh);
        glVertex2f(dx + dw, dy + dh); glVertex2f(dx - dw, dy + dh);
        glEnd();

        int t[6]; time_t now = time(0); struct tm* ti = localtime(&now);
        t[0] = ti->tm_hour / 10; t[1] = ti->tm_hour % 10;
        t[2] = ti->tm_min / 10; t[3] = ti->tm_min % 10;
        t[4] = ti->tm_sec / 10; t[5] = ti->tm_sec % 10;

        float digitW = 0.12f, digitH = 0.16f, gap = 0.05f, startX = dx - 0.48f;
        for (int i = 0; i < 6; i++) {
            drawDigit(startX + (digitW + gap) * i, dy, digitW, digitH, t[i]);
            if (i == 1 || i == 3)drawColon(startX + (digitW + gap) * (i + 0.5f), dy, 0.04f);
        }

        drawHand(hA, outerR * 0.5f, 5, 0, 0, 0, 1, 0.03f);
        drawHand(mA, outerR * 0.75f, 3, 0, 0, 0, 1, 0.03f);
        glPushMatrix(); glTranslatef(innerCX, innerCY, 0);
        drawHand(sA, innerR * 0.8f, 2, 1, 0, 0, 1, innerR * 0.1f); glPopMatrix();

        glfwSwapBuffers(w); glfwPollEvents();
    }
    glfwTerminate(); return 0;
}
