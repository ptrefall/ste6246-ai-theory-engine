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

		Totem::PropertyList<std::string> textures;
    Totem::PropertyList<unsigned int> materialType;
    Totem::PropertyList<irr::core::vector2df> textureScale;
		Totem::Property<irr::scene::ISceneNode*> node;
    Totem::Property<irr::scene::ITerrainSceneNode*> terrain;

		void OnNodeChanged(irr::scene::ISceneNode*const &oldValue, irr::scene::ISceneNode*const &newValue);
	};
}
