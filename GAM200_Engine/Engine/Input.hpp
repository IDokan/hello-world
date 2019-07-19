#pragma once
#include <bitset>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "vector2.hpp"

class Input
{
private:
     std::bitset<GLFW_KEY_LAST> key_triggered;
     std::bitset<GLFW_KEY_LAST> key_pressed;
     std::bitset<GLFW_KEY_LAST> key_released;

     std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_triggered;
     std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_doubleClick;
     std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_pressed;
     std::bitset<GLFW_MOUSE_BUTTON_LAST> mouse_released;

     vector2 mousePosition{};

     double x_offset = 0.0;
     double y_offset = 0.0;

public:
    void Init();
    void TriggeredReset();

    void SetKeyBoardInput(int key, int action);
    void SetMouseInput(int button, int action);
    void SetMousePosition(double x, double y);
    void SetMouseWheel(double x, double y);

    bool IsKeyTriggered(int key);
    bool IsKeyPressed(int key);
    bool IsKeyReleased(int key);

    bool IsMouseTriggered(int button);
    bool IsMousePressed(int button);
    bool IsMouseReleased(int button);
    bool IsMouseDoubleClicked(int button);

    vector2 GetMousePosition();

    double MouseWheelScroll();
};

extern Input input;
// if there are 2 inputs(two keyboards), use extern