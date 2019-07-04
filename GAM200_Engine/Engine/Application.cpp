#include "Application.hpp"
#include <iostream>


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

    glfwSwapInterval(true);
}

void Application::Update(float dt)
{
    fpsEllapsedTime += dt;
    ++fpsFrames;
    if (fpsEllapsedTime >= 1.0f)
    {
        std::cout << fpsFrames << std::endl;

        fpsEllapsedTime = 0;
        fpsFrames = 0;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Application::Clear()
{
}
