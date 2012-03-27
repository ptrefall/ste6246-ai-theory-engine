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
  class TerrainNavGraph;
  typedef std::shared_ptr<TerrainNavGraph> TerrainNavGraphPtr;

	class TerrainNavGraph : public Totem::Component<TerrainNavGraph>
	{
	public:
    TerrainNavGraph(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);
		virtual ~TerrainNavGraph();

		void initialize();

    irr::scene::ITerrainSceneNode *getTerrain() { return terrain.get(); }
    Structures::GraphPtr getGraph() { return graph.get(); }

	private:
    void genGraph();

		EntityWPtr owner;
		irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *driver;

    Totem::Property<std::string> heightmap;
    Totem::Property<irr::scene::ITerrainSceneNode*> terrain;
    Totem::Property<irr::core::vector3df> scale;
    Totem::Property<Structures::GraphPtr> graph;


	};
}
