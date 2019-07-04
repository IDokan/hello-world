#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application
{
private:
    Application() = default;

public:
    static Application* GetApplication();

    void Init();
    void Update(float dt);
    void Clear();

private:
    static Application* app;
    GLFWwindow *window = nullptr;

    float fpsEllapsedTime = 0.f;
    int fpsFrames = 0;
};