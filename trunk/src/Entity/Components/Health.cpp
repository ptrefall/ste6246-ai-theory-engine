#include "Health.h"

#include <iostream>

using namespace Components;
using namespace Totem;

Health::Health(Entity &owner, const std::string &name, EntityManager &entityMgr, irr::scene::ISceneManager &smgr)
: Component(name), owner(owner), entityMgr(entityMgr), smgr(smgr), healthbar(0x0), dmgEventId("DMG"), loadEventId("LOAD")
{
	name_property = owner.addProperty<std::string>("Name", "");
    alive_property = owner.addProperty<bool>("Alive", true);
	health_property = owner.addProperty<float>("Health", 100.0f);
	maxhealth_property = owner.addProperty<float>("MaxHealth", 100.0f);
	sceneNode = owner.addProperty<irr::scene::ISceneNode*>("SceneNode", 0x0);

    health_property.valueChanged().connect(this, &Health::onHealthChanged);
	alive_property.valueChanged().connect(this, &Health::onAliveChanged);

	owner.registerToEvent2<const float&, const std::string&>(dmgEventId).connect(this, &Health::onDmgEvent);
	owner.registerToEvent0(loadEventId).connect(this, &Health::onLoadEvent);
}

Health::~Health()
{
}

void Health::onDmgEvent(const float &dmg, const std::string &attackerName)
{
	//std::cout << attackerName.c_str() << " inflicted " << dmg << " damage to " << name_property.get().c_str() << std::endl;

	health_property -= dmg;
	if(0 < health_property)
	{
		//std::cout << name_property.get().c_str() << "'s remaining health is " << health_property.get() << " hp!" << std::endl;
	}
}

void Health::onLoadEvent()
{
	if(sceneNode.get() == 0x0)
		throw std::exception("SceneNode property must be initializes for the healthbar to work!");

	irr::scene::ISceneCollisionManager* coll = smgr.getSceneCollisionManager();
	healthbar = new irr::scene::HealthSceneNode(sceneNode.get(),&smgr,-1,coll,50,10,irr::core::vector3df(0,0,0));
	healthbar->setProgress((irr::s32)health_property.get());
	healthbar->setScale(irr::core::vector3df(0.02f, 0.02f, 0.02f));
}

void Health::onHealthChanged(const float &/*oldValue*/, const float &newValue)
{
	if(newValue > 0.0f)
		healthbar->setProgress((irr::s32)newValue);
	else 
		alive_property = false;
}

void Health::onAliveChanged(const bool &/*oldValue*/, const bool &newValue)
{
	//If no longer alive, tell the go's player, if there is a player
	if(!newValue)
	{
		//Could send an event here that we died (useful if someone targets us, or if player should be notified in some way, 
		//or the game manager should put us in a pending_deletion list or something...

		//std::cout << name_property.get().c_str() << " died..." << std::endl;
		entityMgr.erase(&owner);
	}
}
