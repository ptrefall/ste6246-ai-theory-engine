#include "EntityManager.h"
#include "Entity.h"

#include <iostream>

using namespace Totem;

EntityManager::~EntityManager()
{
	entities.clear();
}

void EntityManager::update(const double &deltaTime)
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
		}
		pendingDelete.clear();
	}

	for(unsigned int i = 0; i < entities.size(); i++)
		entities[i]->updateComponents(deltaTime);
}

EntityPtr EntityManager::create()
{
	EntityPtr entity = std::make_shared<Entity>();
	entities.push_back(entity);
		return entity;
}

void EntityManager::erase(EntityPtr entity)
{
	pendingDelete.push_back(entity);
}
