#pragma once
#pragma warning(push)
#pragma warning(disable : 4481)

#include <Totem/ComponentContainer.h>
#include <Totem/PropertyContainer.h>
#include <Totem/PropertyListContainer.h>
#include <Totem/Addons/EventSystem.h>

#include <memory>

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity> EntityWPtr;

class Entity 
	:	public Totem::ComponentContainer<>, 
		public Totem::PropertyContainer<>, 
		public Totem::PropertyListContainer<>, 
		public Totem::Addon::EventSystem<>
{
public:	
	Entity() {}
};

#pragma warning(pop)
