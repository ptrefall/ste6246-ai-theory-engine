#include "PathFinder.h"

using namespace Component;

PathFinder::PathFinder(const EntityPtr &owner, const std::string &name, Structures::GraphPtr graph)
	: Totem::Component<PathFinder>(name), owner(owner), smgr(smgr), driver(driver)
{
  this->graph = owner->add<Structures::GraphPtr>("NavGraph", graph);
  position = owner->add<irr::core::vector3df>("Position", irr::core::vector3df());
  goal = owner->add<EntityPtr>("Goal", nullptr);
  searchAlg = owner->add<Algorithms::Search::ISearchPtr>("SearchAlg", nullptr);
}

PathFinder::~PathFinder()
{
}

void PathFinder::initialize(const EntityPtr &target, const Algorithms::Search::ISearchPtr &search)
{
  this->goal = target;
  this->searchAlg = search;
  findPath();
}

void PathFinder::findPath()
{
  auto start_node = getNodeFromPos(position.get());
  auto goal_node = getNodeFromPos(goal.get()->get<irr::core::vector3df>("Position").get());
  if(start_node == nullptr || goal_node == nullptr || searchAlg.get() == nullptr || graph.get() == nullptr)
    return;

  path = searchAlg.get()->search(graph.get(), start_node, goal_node);
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
