#pragma once

#include "../Entity.h"

#include <Totem/Component.h>
#include <Irrlicht\irrlicht.h>
#include <string>

namespace Component
{
	class Textured : public Totem::Component<Textured>
	{
	public:
		Textured(const EntityPtr &owner, const std::string &name, irr::video::IVideoDriver* driver, const std::string &res_dir);
		virtual ~Textured();

	private:
		EntityWPtr owner;
		irr::video::IVideoDriver* driver;
		const std::string &res_dir;

		Totem::Property<std::string> texture;
		Totem::Property<irr::scene::ISceneNode*> node;

		void OnNodeChanged(irr::scene::ISceneNode*const &oldValue, irr::scene::ISceneNode*const &newValue);
	};
}
