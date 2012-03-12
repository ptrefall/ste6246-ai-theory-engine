#include "EntityManager.h"
#include "Entity.h"

#include <iostream>

using namespace Totem;

EntityManager::~EntityManager()
{
	for(unsigned int i = 0; i < entities.size(); i++)
		delete entities[i];
}

void EntityManager::update(const float &deltaTime)
{
	if(!pendingDelete.empty())
	{
		for(unsigned int i = 0; i < pendingDelete.size(); i++)
		{
			for(unsigned int j = 0; j < entities.size(); j++)
			{
				if(entities[j] == pendingDelete[i])
				{
					//This is a vector element removal trick that's O(1)
					entities[j] = entities.back();
					entities.pop_back();
					break;
				}
			}
			delete pendingDelete[i];
		}
		pendingDelete.clear();
	}

	for(unsigned int i = 0; i < entities.size(); i++)
		entities[i]->updateComponents(deltaTime);
}

Entity &EntityManager::create(ComponentFactory &factory)
{
	Entity *entity = new Entity(factory, terrain);
	entities.push_back(entity);
		return *entity;
}

void EntityManager::erase(Entity *entity)
{
	pendingDelete.push_back(entity);
}
