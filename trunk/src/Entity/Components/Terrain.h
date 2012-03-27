#pragma once

#include "../Entity.h"

#include <Totem/Component.h>
#include <Irrlicht\irrlicht.h>

#include <string>

namespace Component
{
  class Terrain;
  typedef std::shared_ptr<Terrain> TerrainPtr;

	class Terrain : public Totem::Component<Terrain>
	{
	public:
		Terrain(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr);
		virtual ~Terrain();

		void initialize();

		irr::scene::ISceneNode *getNode() { return node.get(); }
    irr::scene::ITerrainSceneNode *getTerrain() { return terrain.get(); }

	private:
		EntityWPtr owner;
		irr::scene::ISceneManager *smgr;

    Totem::Property<std::string> heightmap;
		Totem::Property<float> size;
		Totem::Property<irr::scene::ISceneNode*> node;
    Totem::Property<irr::scene::ITerrainSceneNode*> terrain;
		Totem::Property<irr::scene::ISceneNode*> parent;
		Totem::Property<irr::core::vector3df> position;
		Totem::Property<irr::core::vector3df> rotation;
		Totem::Property<irr::core::vector3df> scale;

		void OnPositionChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue);
		void OnRotationChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue);
		void OnScaleChanged(const irr::core::vector3df &oldValue, const irr::core::vector3df &newValue);
	};
}
