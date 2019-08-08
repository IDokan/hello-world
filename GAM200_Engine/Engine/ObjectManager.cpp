#include "ObjectManager.hpp"
#include "StateManager.hpp"
#include <iostream>


ObjectManager* ObjectManager::manager = nullptr;
ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
}

ObjectManager* ObjectManager::GetObjectManager()
{
	if(manager == nullptr)
		 manager = new ObjectManager;
	return manager;
}

void ObjectManager::Init()
{
	objects.clear();
	delete_obj.clear();
}

void ObjectManager::Update(float dt)
{
	if (StateManager::GetStateManager()->is_restart)
	{

		delete_obj.clear();

		// auto&& tmp;
		for (const auto & obj : objects)
		{
			for (const auto & comp : obj->GetComponentContainer())
			{
				comp->Update(dt);
			}

			if (obj->GetIsDead())
			{
				delete_obj.push_back(obj);
			}
		}

		// Delete in separate loop
		for (const auto& obj : delete_obj)
		{
			DeleteObject(obj);
		}
	}
	else
	{
		std::cout << "Object Manager Stop!" << std::endl;
	}
}

void ObjectManager::Clear()
{
	objects.clear();
	delete_obj.clear();

	delete GetObjectManager();
	// To prevent memory leak, should set obj_m pointing to nullptr
	// obj_m = nullptr;
}

void ObjectManager::AddObject(Object* obj)
{
	//for (const auto& cmp : obj->GetComponentContainer())
	//{
	//	cmp->Init(obj);
	//}

	objects.push_back(std::shared_ptr<Object>(obj));
}

void ObjectManager::DeleteObject(std::shared_ptr<Object> obj)
{
	objects.erase(std::find(objects.begin(), objects.end(), obj));
}
