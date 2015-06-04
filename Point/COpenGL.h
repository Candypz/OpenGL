#ifndef _COPENGL_H_
#define _COPENGL_H_

#define PI      3.14159
#define TWO_PI  PI*2.0
#define HALF_PI PI/2.0

class COpenGL {
public:
    COpenGL();
    virtual ~COpenGL();

    bool init();
    bool shutdown();
    void setupProjection(int width,int height);//…Ë÷√Õ∂”∞
    void prepare(float dt);
    void render();
private:
    int m_windowWidth;
    int m_windowHeight;
    float m_angle;
};

#endif