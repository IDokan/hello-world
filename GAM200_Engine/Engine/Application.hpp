#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vector2.hpp"

class Application
{
private:
    Application() = default;

public:
    static Application* GetApplication();

    void Init();
    void Update(float dt);
    void Clear();

    vector2 GetWindowSize()
    {
        return window_size;
    }

private:
    static Application* app;
    GLFWwindow *window = nullptr;

    vector2 window_size;
    float fpsEllapsedTime = 0.f;
    int fpsFrames = 0;
};