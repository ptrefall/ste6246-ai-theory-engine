#pragma once

#include <Irrlicht\irrlicht.h>
#include <memory>
#include <vector>

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;

class EntityManager;
typedef std::shared_ptr<EntityManager> EntityManagerPtr;
typedef std::weak_ptr<EntityManager> EntityManagerWPtr;

class EntityManager
{
public:
	EntityManager() {}
	~EntityManager();

	void update(const double &deltaTime);

	EntityPtr create();
	void erase(EntityPtr entity);
	std::vector<EntityPtr> &getEntities() { return entities; }

protected:
	std::vector<EntityPtr> entities;
	std::vector<EntityPtr> pendingDelete;
};
