#pragma once

#include "State.hpp"
#include  <iostream>
#include <string>
#include "Input.hpp"
#include <GLFW/glfw3.h>

class Menu : public State
{
public:
	Menu()
	{
		current_state_info = GameState::Menu;
	}

	virtual void Load()
	{
		std::cout << "Init to Menu Level !!" << std::endl;
	}
	virtual  void Update(float dt)
	{
		std::cout << "I am a Menu Level" << std::endl;

		if(input.IsKeyTriggered(GLFW_KEY_N))
		{
			is_next = true;
			next_level = "Level1";
		}
	}

	virtual  void Unload()
	{
		next_level = {};
		is_next = false;
	}
};
