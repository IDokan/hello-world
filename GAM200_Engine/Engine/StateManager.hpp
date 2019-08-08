#pragma once

#include  <unordered_map>
#include <memory>
#include  "State.hpp"

class StateManager
{
public:
	static  StateManager* GetStateManager();

	void Init();
	void Update(float dt);
	void Delete();

	void AddState(std::string name, State* state);
	//void DeleteState(std::shared_ptr<State> state);

	bool is_restart = true;
private:
	static StateManager* m_state_manager;

	std::unordered_map < std::string, std::shared_ptr<State>> m_states;
	State* current_state = nullptr;


};