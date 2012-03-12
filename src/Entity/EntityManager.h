#pragma once

#include <Totem/types_config.h>
#include <Irrlicht\irrlicht.h>

namespace Totem { class ComponentFactory; }

class Entity;
class EntityManager
{
public:
	EntityManager(irr::scene::ITerrainSceneNode& terrain) : nextEntityId(0), terrain(terrain) {}
	~EntityManager();

	void update(const float &deltaTime);

	Entity &create(Totem::ComponentFactory &factory);
	void erase(Entity *Entity);
	std::vector<Entity*> &getEntities() { return entities; }

protected:
	std::vector<Entity*> entities;
	std::vector<Entity*> pendingDelete;
	unsigned int nextEntityId;
	irr::scene::ITerrainSceneNode& terrain;
};
