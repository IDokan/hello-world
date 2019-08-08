#pragma once


enum class GameState
{
	Menu, Game, Credit, None
};

class State
{
public:

	virtual void Load() = 0;
	virtual void Update(float dt) = 0;
	virtual void Unload() = 0;

public:
	void MoveLevel(std::string name)
	{
		next_level = name;
	}
	std::string GetNextLevelName() { return next_level; }
	bool IsNextLevel() { return  is_next; }
	GameState GetStateInfo() { return current_state_info; }
	
protected:
	GameState current_state_info = GameState::None;
	std::string next_level;
	bool is_next = false;
};
