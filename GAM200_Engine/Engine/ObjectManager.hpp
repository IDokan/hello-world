#pragma once

#include <vector>
#include "Object.hpp"
#include <memory>
#include <unordered_map>

class ObjectManager
{
public:
	~ObjectManager();

	static ObjectManager* GetObjectManager();

	void Init();
	void Update(float dt);
	void Clear();

	void AddObject(Object* obj);
	void DeleteObject(std::shared_ptr<Object> obj);

	std::vector<std::shared_ptr<Object>>& GetObjectManagerContainer() { return objects; }

private:
	ObjectManager();
	static ObjectManager* manager;

	// Tile, many objects -> vector
	// Puzzle, Casual -> map (easy to get specific object)
	std::vector<std::shared_ptr<Object>> objects{};
	//std::unordered_map<std::string, std::unique_ptr<Object>> objectsMap;
	std::vector<std::shared_ptr<Object>>delete_obj{};
};
