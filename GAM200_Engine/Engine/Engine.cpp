#include "Engine.hpp"
#include <iostream>
#include "Application.hpp"

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
}

void Engine::Clear()
{
}
