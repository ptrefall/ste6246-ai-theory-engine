#pragma once

#include <Totem/Component.h>
#include "../Entity.h"
#include "../EntityManager.h"

#include <Irrlicht\irrlicht.h>
#include <SceneNode\HealthSceneNode.h>

namespace Components
{
	class Health : public Totem::Component
	{
	public:
		COMPONENT_2(Entity, Health, EntityManager, irr::scene::ISceneManager)
		Health(Entity &owner, const std::string &name, EntityManager &entityMgr, irr::scene::ISceneManager &smgr);
		virtual ~Health();

	protected:
		Totem::Property<std::string> name_property;
		Totem::Property<bool> alive_property;
		Totem::Property<float> health_property;
		Totem::Property<float> maxhealth_property;

		void onHealthChanged(const float &oldValue, const float &newValue);
		void onAliveChanged(const bool &oldValue, const bool &newValue);

		void onDmgEvent(const float &dmg, const std::string &attackerName);
		void onLoadEvent();
		
		T_HashedString dmgEventId;
		T_HashedString loadEventId;

		EntityManager &entityMgr;
		irr::scene::ISceneManager &smgr;

		irr::scene::HealthSceneNode *healthbar;
		Totem::Property<irr::scene::ISceneNode*> sceneNode;

	};
}
