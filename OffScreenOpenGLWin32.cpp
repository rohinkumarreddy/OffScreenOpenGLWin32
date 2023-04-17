#if 0
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}
#else
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLU32.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

_Use_decl_annotations_ int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd = NULL;
    MSG msg;
    WNDCLASS wc = {};

    // Create the window class
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyOpenGLWindowClass";
    RegisterClass(&wc);

    // Create the window
    hwnd = CreateWindow(wc.lpszClassName, L"My OpenGL Window", WS_OVERLAPPEDWINDOW, 0, 0, 640, 480, NULL, NULL, hInstance, NULL);
    //hwnd = CreateWindow(wc.lpszClassName, L"My OpenGL Window", WS_POPUP, 0, 0, 640, 480, NULL, NULL, hInstance, NULL);


    // Show the window
    ShowWindow(hwnd, SW_SHOWNORMAL);//SW_HIDE
    //ShowWindow(hwnd, SW_HIDE);

    // Get the device context
    HDC hdc = GetDC(hwnd);

    // Set up the pixel format descriptor
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    // Choose a pixel format
    int pixelFormat = ChoosePixelFormat(hdc, &pfd);

    // Set the pixel format
    SetPixelFormat(hdc, pixelFormat, &pfd);

    // Create the OpenGL context
    HGLRC hglrc = wglCreateContext(hdc);

    // Make the context current
    wglMakeCurrent(hdc, hglrc);

    // Set up OpenGL
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Render loop
    //while (true)
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw your scene here
        glBegin(GL_LINES);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 1, 0);
		glVertex3d(0, 0, 1);
        glVertex3d(1, 0, 0);
        glEnd();
        // Swap buffers
        SwapBuffers(hdc);

        // Sleep for a bit to avoid busy-waiting
        //Sleep(1);
    }

    // Clean up
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
    UnregisterClass(wc.lpszClassName, hInstance);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

#endif

#if 0
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <thread>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "GLU32.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void RenderThread(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS wc = {};

    // Create the window class
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MyOpenGLWindowClass";
    RegisterClass(&wc);

    // Create the window
    hwnd = CreateWindow(wc.lpszClassName, L"My OpenGL Window", WS_OVERLAPPEDWINDOW, 0, 0, 640, 480, NULL, NULL, hInstance, NULL);

    // Show the window
    ShowWindow(hwnd, SW_HIDE);

    // Start the render thread
    std::thread renderThread(RenderThread, hwnd);

    // Message loop
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up
    renderThread.join();
    DestroyWindow(hwnd);
    UnregisterClass(wc.lpszClassName, hInstance);

    return 0;
}

void RenderThread(HWND hwnd)
{
    // Get the device context
    HDC hdc = GetDC(hwnd);

    // Set up the pixel format descriptor
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    // Choose a pixel format
    int pixelFormat = ChoosePixelFormat(hdc, &pfd);

    // Set the pixel format
    SetPixelFormat(hdc, pixelFormat, &pfd);

    // Create the OpenGL context
    HGLRC hglrc = wglCreateContext(hdc);

    // Make the context current
    wglMakeCurrent(hdc, hglrc);

    // Set up OpenGL
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Render loop
    while (true)
    {
        // Render the scene
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw your scene here

        // Swap buffers
        SwapBuffers(hdc);
    }

    // Clean up
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

#endif