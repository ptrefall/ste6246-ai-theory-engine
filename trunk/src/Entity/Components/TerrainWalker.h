#pragma once

#include "../Entity.h"

#include "../../Structures/Graph/Graph.h"
#include "../../Structures/Graph/GraphEdge.h"
#include "../../Structures/Graph/GraphNode.h"

#include <Totem/Component.h>
#include <Irrlicht\irrlicht.h>

#include <string>

namespace Component
{
  class TerrainWalker;
  typedef std::shared_ptr<TerrainWalker> TerrainWalkerPtr;

	class TerrainWalker : public Totem::Component<TerrainWalker>
	{
	public:
    TerrainWalker(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr, irr::scene::ITerrainSceneNode *terrain);
		virtual ~TerrainWalker();

		void initialize();
    void update(const float &dt) override;

    irr::scene::ISceneNode *getNode() { return node.get(); }
    irr::scene::ITerrainSceneNode *getTerrain() { return terrain; }

	private:
		EntityWPtr owner;
		irr::scene::ISceneManager *smgr;
    irr::scene::ITerrainSceneNode *terrain;

    Totem::Property<irr::scene::ISceneNode*> node;
	};
}
