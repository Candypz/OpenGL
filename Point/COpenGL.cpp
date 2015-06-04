#include "stdafx.h"
#include "COpenGL.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma warning(disable:4305)//禁止把单精度变成双精度


COpenGL::COpenGL() {

}

COpenGL::~COpenGL() {
    
}

bool COpenGL::init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    m_angle = 0.0f;

    return true;
}

bool COpenGL::shutdown() {

    return true;
}

void COpenGL::setupProjection(int width, int height) {
    if (height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);//投影矩阵
    glLoadIdentity();//复位

    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);//模型视图矩阵
    glLoadIdentity();

    m_windowWidth = width;
    m_windowHeight = height;
}


void COpenGL::prepare(float dt) {
    m_angle = m_angle + 0.1f;
    if (m_angle >= 360.0f) {
        m_angle = 0.0f;
    }
}

void COpenGL::render() {
    //opengl绘制
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0f, 0.0f, 6.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f);

    //glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(m_angle, 0.0f, 0.0f, 1.0f);

    glPointSize(30.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POINTS);

    glVertex3f(0.0f, 0.0f, 0.0f);

    glEnd();


}