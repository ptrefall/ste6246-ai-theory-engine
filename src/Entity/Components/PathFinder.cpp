#include "PathFinder.h"

using namespace Component;

PathFinder::PathFinder(const EntityPtr &owner, const std::string &name, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver)
	: Totem::Component<PathFinder>(name), owner(owner), smgr(smgr), driver(driver)
{
  position = owner->add<irr::core::vector3df>("Position", irr::core::vector3df());
  graph = owner->add<Structures::GraphPtr>("NavGraph", nullptr);
  goal = owner->add<EntityPtr>("Goal", nullptr);
}

PathFinder::~PathFinder()
{
}

void PathFinder::initialize(const EntityPtr &target, const Algorithms::Search::ISearchPtr &search)
{
  this->search = search;

}

void PathFinder::findPath()
{
  Structures::GraphNodePtr start_node = getNodeFromPos(position.get());
  Structures::GraphNodePtr goal_node = getNodeFromPos(goal.get()->get<irr::core::vector3df>("Position").get());
  if(start_node == nullptr || goal_node == nullptr)
    return;

  search->search(graph.get(), start_node, goal_node);
}

Structures::GraphNodePtr PathFinder::getNodeFromPos(const irr::core::vector3df &posit)
{
  for(auto i = 0; i < graph.get()->getNodes().size(); i++)
  {
    auto &node = graph.get()->getNodes()[i];
    const irr::core::vector3df &pos = node->get<irr::core::vector3df>("Position").get();
    if((unsigned int)pos.X*1000000.0f == (unsigned int)posit.X*1000000.0f &&
       (unsigned int)pos.Y*1000000.0f == (unsigned int)posit.Y*1000000.0f)
    {
      return node;
    }
  }
  return nullptr;
}
