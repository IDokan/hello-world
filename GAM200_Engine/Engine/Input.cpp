#include "Input.hpp"
#include <assert.h>
#include <chrono>
#include "Application.hpp"

Input input;

void Input::Init()
{
    key_pressed.reset(); // false로 초기화
    key_released.reset();
    key_triggered.reset();

    mouse_doubleClick.reset();
    mouse_pressed.reset();
    mouse_released.reset();
    mouse_triggered.reset();

    x_offset = 0.0;
    y_offset = 0.0;
}

void Input::TriggeredReset()
{
    key_triggered.reset();
    mouse_triggered.reset();
    mouse_doubleClick.reset();
}

void Input::SetKeyBoardInput(int key, int action)
{
    assert(key > -1 && key < GLFW_KEY_LAST);

    switch (action)
    {
    case GLFW_PRESS:
        key_triggered.set(key);
        key_pressed.set(key);
        key_released.reset(key);
        break;
    case GLFW_RELEASE:
        key_triggered.reset(key);
        key_pressed.reset(key);
        key_released.set(key);
        break;
    default:
        break;
    }
}

void Input::SetMouseInput(int button, int action)
{
    assert(button > -1 && button < GLFW_MOUSE_BUTTON_LAST);

    switch (action)
    {
    case GLFW_PRESS:
        mouse_triggered.set(button);
        mouse_pressed.set(button);
        mouse_released.reset(button);        
        break;
    case GLFW_RELEASE:
    {
        static auto before = std::chrono::system_clock::now();
        auto now = std::chrono::system_clock::now();
        double diff_ms = std::chrono::duration<double, std::milli>(now - before).count();
        before = now;

        if (diff_ms > 10 && diff_ms < 200)
        {
            mouse_doubleClick.set(button);
        }
        else
        {
            mouse_doubleClick.reset(button);
        }
        mouse_triggered.reset(button);
        mouse_pressed.reset(button);
        mouse_released.set(button);
        break;
    }
    default:
        break;
    }
}
void Input::SetMousePosition(double x, double y)
{
    float w = Application::GetApplication()->GetWindowSize().x;
    float h = Application::GetApplication()->GetWindowSize().y;

    mousePosition.x = -(w / 2.0f - x);
    mousePosition.y = h / 2.0f - y;
}
void Input::SetMouseWheel(double x, double y)
{
    x_offset = x;
    y_offset = y;
}

bool Input::IsKeyTriggered(int key)
{
    return key_triggered[key];
}

bool Input::IsKeyPressed(int key)
{
    return key_pressed[key];
}

bool Input::IsKeyReleased(int key)
{
    return key_released[key];
}

bool Input::IsMouseTriggered(int button)
{
    return mouse_triggered[button];
}

bool Input::IsMousePressed(int button)
{
    return mouse_pressed[button];;
}

bool Input::IsMouseReleased(int button)
{
    return mouse_released[button];;
}

bool Input::IsMouseDoubleClicked(int button)
{
    return mouse_doubleClick[button];
}

vector2 Input::GetMousePosition()
{
    return mousePosition;
}

double Input::MouseWheelScroll()
{
    return y_offset;
}
