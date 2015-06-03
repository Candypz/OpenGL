// Text1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Text1.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#define MAX_LOADSTRING 100

HDC g_HDC;
HWND g_hWnd;
float angle = 0.0f;

void setupPixeFormat(HDC hdc) {
    int nPixelFormat;//像素格式
    static PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,//版本号
        PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER,//双缓冲
        PFD_TYPE_RGBA,//颜色类型
        32,
        0, 0, 0, 0, 0, 0,
        0, 0, 0,
        0, 0, 0, 0,
        16,//16位z缓存
        0, 0,
        PFD_MAIN_PLANE,
        0, 0, 0, 0,
    };
    nPixelFormat = ChoosePixelFormat(hdc, &pfd);//匹配
    SetPixelFormat(hdc, nPixelFormat, &pfd);
}

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO:  在此放置代码。
    MSG msg;
    HACCEL hAccelTable;

    bool done;

    // 初始化全局字符串
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_TEXT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEXT1));

    done = false;
    while (!done) {
        PeekMessage(&msg, g_hWnd, NULL, NULL, PM_REMOVE);
        if (msg.message == WM_QUIT) {
            done = true;
        }
        else {
            //opengl绘制
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glLoadIdentity();

            angle = angle + 0.1f;
            if (angle >= 360.0f) {
                angle = 0.0f;
            }

            glTranslatef(0.0f, 0.0f, -5.0f);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);

            glColor3f(1.0f, 0.0f, 0.0f);
            glBegin(GL_TRIANGLES);

            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 1.0f, 0.0f);

            glEnd();

            SwapBuffers(g_HDC);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEXT1));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = NULL;//(HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    HWND hWnd;

    hInst = hInstance; // 将实例句柄存储在全局变量中



    hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    g_hWnd = hWnd;

    if (!hWnd) {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    static HDC hdc;
    static HGLRC hRC;
    int height, width;

    switch (message) {
        case WM_CREATE:
            hdc = GetDC(hWnd);
            g_HDC = hdc;
            setupPixeFormat(hdc);
            hRC = wglCreateContext(hdc);//opengl绘制
            wglMakeCurrent(hdc, hRC);
            break;

        case WM_COMMAND:
            wmId = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
        case WM_SIZE:
            height = HIWORD(lParam);
            width = LOWORD(lParam);
            if (height == 0) {
                height = 1;
            }
            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);//投影矩阵
            glLoadIdentity();//复位

            gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

            glMatrixMode(GL_MODELVIEW);//模型视图矩阵
            glLoadIdentity();
            break;
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            // TODO:  在此添加任意绘图代码...


            EndPaint(hWnd, &ps);
            break;
        case WM_CLOSE:
        case WM_QUIT:
        case WM_DESTROY:
            wglMakeCurrent(hdc, NULL);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    switch (message) {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}
