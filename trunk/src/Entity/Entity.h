#pragma once

#include <Totem/ComponentHandler.h>
#include <Totem/PropertyHandler.h>
#include <Totem/PropertyListHandler.h>
#include <Totem/Addons/TemplateEventHandler.h>
#include <Totem/Addons/DelegateHandler.h>

#include <Irrlicht\irrlicht.h>

class Entity :	public Totem::ComponentHandler<Entity>, 
				public Totem::PropertyHandler<>, 
				public Totem::PropertyListHandler<>, 
				public Totem::Addon::TemplateEventHandler,
				public Totem::Addon::DelegateHandler
{
public:
	/// Constructor
	Entity(Totem::ComponentFactory &factory, irr::scene::ITerrainSceneNode& terrain)
#pragma warning(suppress: 4355)
		: Totem::ComponentHandler<Entity>(*this, factory), terrain(terrain)
	{
	}

	/// Destructor
	virtual ~Entity() {}

	irr::scene::ITerrainSceneNode &getTerrain() { return terrain; }

protected:
	irr::scene::ITerrainSceneNode& terrain;
};
