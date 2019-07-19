#pragma once
#include "Timer.hpp"
class Application;

class Engine
{
public:
    Engine() = default;
    void Init();
    void Update();
    void Clear();

    bool IsRunning() noexcept
    {
        return isRunnig;
    }

private:
    bool isRunnig = false;
    float m_dt;
    Timer gameTimer;
};