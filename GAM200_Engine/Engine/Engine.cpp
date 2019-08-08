#include "Engine.hpp"
#include <iostream>
#include "Application.hpp"
#include "Input.hpp"
#include "ObjectManager.hpp"
#include "Player.hpp"
#include "StateManager.hpp"
#include "Menu.hpp"
#include "Level1.hpp"

namespace
{
    Application* app_ = nullptr;
	ObjectManager* manager = nullptr;
	StateManager* state_manager = nullptr;
}

void Engine::Init()
{
    app_ = Application::GetApplication();
	manager = ObjectManager::GetObjectManager();
	state_manager = StateManager::GetStateManager();
	
	app_->Init();
	manager->Init();
	state_manager->Init();

	state_manager->AddState("Level1", new Level1());
	state_manager->AddState("Menu", new Menu());

	Object* tmp = new Object();
	tmp->AddComponent(new Player());
	manager->AddObject( tmp);

    gameTimer.Reset();

    isRunnig = false;
}

void Engine::Update()
{

    m_dt = static_cast<float>(gameTimer.GetElapsedSeconds());
    gameTimer.Reset();

    app_->Update(m_dt);
	manager->Update(m_dt);
	state_manager->Update(m_dt);

	// PAUSE..
	// make pause in specific manager

	if (input.IsKeyPressed(GLFW_KEY_1))
	{
		state_manager->is_restart = !state_manager->is_restart;
	}

    if (input.IsKeyTriggered(GLFW_KEY_D))
    {
		manager->GetObjectManagerContainer()[0]->SetDead(true);
    }
    /*if (input.IsKeyTriggered(GLFW_KEY_A))
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
    std::cout << input.GetMousePosition().x << ", " << input.GetMousePosition().y << std::endl;*/

    if (manager->GetObjectManagerContainer().empty())
    {
		std::cout << "Object Manager is empty!\n";
    }
	//std::cout << "ObjectManager Size: " << manager->GetObjectManagerContainer().size() << std::endl;

}

void Engine::Clear()
{
}
