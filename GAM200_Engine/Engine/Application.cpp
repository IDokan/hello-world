#include "Application.hpp"
#include <iostream>
#include "Input.hpp"

namespace {
    void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    void MousePositionCallback(GLFWwindow* window, double x_pos, double y_pos);
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void MouseWheelScroll(GLFWwindow* window, double x_offset, double y_offset);
}

Application* Application::app = nullptr;

Application* Application::GetApplication()
{
    if (app == nullptr)
    {
        app = new Application;
    }
    return app;
}

void Application::Init()
{
    // Context Profile is Core
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Context Version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Multi-sampling isi enabled and configured to using 4 samples
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Depth buffer is enabled.
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    // Double buffering is enabled.
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

    if (!glfwInit())
    {
        std::exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(1280,1080,"engineTest",nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetScrollCallback(window, MouseWheelScroll);
    glfwSetCursorPosCallback(window, MousePositionCallback);

    glfwSwapInterval(true);
}

void Application::Update(float dt)
{
    input.TriggeredReset();

    fpsEllapsedTime += dt;
    ++fpsFrames;
    if (fpsEllapsedTime >= 1.0f)
    {
        std::cout << fpsFrames << std::endl;

        fpsEllapsedTime = 0;
        fpsFrames = 0;
    }
    int w, h; // just prototype 
    glfwGetWindowSize(window, &w, &h); // just prototype 
    window_size.x = (float)w; // just prototype 
    window_size.y = (float)h; // just prototype 
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Application::Clear()
{
}

namespace {
    void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        input.SetKeyBoardInput(key, action);
    }
    void MousePositionCallback(GLFWwindow* window, double x_pos, double y_pos)
    {
        input.SetMousePosition(x_pos, y_pos);
    }
    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        input.SetMouseInput(button, action);
    }
    void MouseWheelScroll(GLFWwindow* window, double x_offset, double y_offset)
    {
        input.SetMouseWheel(x_offset, y_offset);
    }
}