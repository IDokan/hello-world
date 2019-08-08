#pragma once

#include "State.hpp"
#include  <iostream>
#include <string>
#include "Input.hpp"
#include <GLFW/glfw3.h>

class Level1 : public State
{
public:
	Level1()
	{
		current_state_info = GameState::Game;
	}

	virtual void Load()
	{
		std::cout << "Init to Level1 Level !!" << std::endl;
	}
	virtual  void Update(float dt)
	{
		std::cout << "I am a Level1 Level" << std::endl;

		if (input.IsKeyTriggered(GLFW_KEY_N))
		{
			is_next = true;
			next_level = "Menu";
		}
	}

	virtual  void Unload()
	{
		next_level = {};
		is_next = false;
	}
};
