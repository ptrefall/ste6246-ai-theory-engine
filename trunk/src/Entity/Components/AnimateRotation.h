#pragma once

#include "../Entity.h"

#include <Totem/Component.h>
#include <Irrlicht\irrlicht.h>

namespace Component
{
	class AnimateRotation : public Totem::Component<AnimateRotation>
	{
	public:
		AnimateRotation(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr);
		virtual ~AnimateRotation();

	private:
		EntityWPtr owner;
		irr::scene::ISceneManager *smgr;

		Totem::Property<irr::core::vector3df> speed;
		Totem::Property<irr::scene::ISceneNode*> node;

		void OnNodeChanged(irr::scene::ISceneNode*const &oldValue, irr::scene::ISceneNode*const &newValue);
	};
}
