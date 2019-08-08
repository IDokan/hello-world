#include  "StateManager.hpp"
#include <iostream>

StateManager* StateManager::m_state_manager = nullptr;

StateManager* StateManager::GetStateManager()
{
	if (m_state_manager == nullptr)
		m_state_manager = new StateManager();

	return m_state_manager;
}
void StateManager::Init()
{
	current_state = nullptr;
	m_states.clear();
}

void StateManager::Update(float dt)
{
	if (is_restart)
	{
		current_state->Update(dt);

		if (current_state->IsNextLevel())
		{
			std::string temp_name = current_state->GetNextLevelName();
			current_state->Unload();
			current_state = m_states.find(temp_name)->second.get();
			current_state->Load();
		}
	}
	else
	{
		std::cout << "Resume!\n";
	}
}

void StateManager::Delete()
{
	current_state = nullptr;
	m_states.clear();
}

void StateManager::AddState(std::string name, State* state)
{
	auto temp = std::make_pair(name, state);
	if (current_state == nullptr) {
		if (state->GetStateInfo() == GameState::Menu)
		{
			current_state = state;
			current_state->Load();
		}
	}

	m_states.insert(temp);
}

