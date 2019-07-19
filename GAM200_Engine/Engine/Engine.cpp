#include "Engine.hpp"
#include <iostream>
#include "Application.hpp"
#include "Input.hpp"

namespace
{
    Application* app_ = nullptr;
}

void Engine::Init()
{
    app_ = Application::GetApplication();

    app_->Init();

    gameTimer.Reset();

    isRunnig = false;
}

void Engine::Update()
{

    m_dt = static_cast<float>(gameTimer.GetElapsedSeconds());
    gameTimer.Reset();

    app_->Update(m_dt);

    if (input.IsKeyTriggered(GLFW_KEY_A))
    {
        std::cout << "A triggered" << std::endl;
    }
    if (input.IsKeyPressed(GLFW_KEY_A))
    {
        std::cout << "A pressed" << std::endl;
    }
    if (input.IsMouseDoubleClicked(GLFW_MOUSE_BUTTON_LEFT))
    {
        std::cout << "double clicked" << std::endl;
    }
    std::cout << input.GetMousePosition().x << ", " << input.GetMousePosition().y << std::endl;
}

void Engine::Clear()
{
}
