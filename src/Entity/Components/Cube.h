#pragma once

#include "../Entity.h"

#include <Totem/Component.h>
#include <Irrlicht\irrlicht.h>

namespace Component
{
	class Cube : public Totem::Component<Cube>
	{
	public:
		Cube(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr);
		virtual ~Cube();

		void initialize();

	private:
		EntityWPtr owner;
		irr::scene::ISceneManager *smgr;

		Totem::Property<float> size;
		Totem::Property<irr::scene::ISceneNode*> node;
		Totem::Property<irr::scene::ISceneNode*> parent;
		Totem::Property<irr::core::vector3df> position;
		Totem::Property<irr::core::vector3df> rotation;
		Totem::Property<irr::core::vector3df> scale;

		void OnPositionChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue);
		void OnRotationChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue);
		void OnScaleChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue);
	};
}
