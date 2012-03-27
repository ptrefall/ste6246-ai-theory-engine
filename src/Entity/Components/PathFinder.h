#pragma once

#include "../Entity.h"

#include "../../Structures/Graph/Graph.h"
#include "../../Structures/Graph/GraphEdge.h"
#include "../../Structures/Graph/GraphNode.h"

#include "../../Algorithms/Search/ISearch.h"

#include <Totem/Component.h>
#include <Irrlicht\irrlicht.h>

#include <string>

namespace Component
{
	class PathFinder : public Totem::Component<PathFinder>
	{
	public:
    PathFinder(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);
		virtual ~PathFinder();

		void initialize(const EntityPtr &target, const Algorithms::Search::ISearchPtr &search);

	private:
    void findPath();
    Structures::GraphNodePtr getNodeFromPos(const irr::core::vector3df &posit);

		EntityWPtr owner;
		irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *driver;

    Totem::Property<irr::core::vector3df> position;
    Totem::Property<Structures::GraphPtr> graph;
    Totem::Property<EntityPtr> goal;

    Algorithms::Search::ISearchPtr search;
	};
}
