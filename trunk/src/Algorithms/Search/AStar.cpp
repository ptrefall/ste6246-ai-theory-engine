#include "AStar.h"

#include <Irrlicht\irrlicht.h>
#include <algorithm>

using namespace Algorithms;
using namespace Search;

using namespace Structures;

AStar::AStar()
  : steps(0)
{
}

AStar::~AStar()
{
}

std::vector<TreeEdgePtr> AStar::search(const TreePtr &tree, const TreeNodePtr &start, const TreeNodePtr &goal)
{
  std::vector<TreeEdgePtr> path;
  std::list<TreeNodePtr> queue;
  //visit(queue, start, goal, path);
  tree->clearVisited();
  return path;
}

std::vector<GraphEdgePtr> AStar::search(const GraphPtr &graph, const GraphNodePtr &start, const GraphNodePtr &goal)
{
  std::vector<GraphEdgePtr> path;
  initialize(graph, start, goal);
  while(!open.empty())
  {
    if(step(graph, start, goal, path))
		break;
  }
  constructPath(goal_node->node, path);
  graph->clearVisited();
  return path;
}

void AStar::initialize(const Structures::GraphPtr &graph, const Structures::GraphNodePtr &start, const Structures::GraphNodePtr &goal)
{
  start_node = std::make_shared<AStarNode>();
  start_node->node = start;
  start_node->G = 0.0f;
  start_node->H = goalDistanceEstimate(graph, start, goal);
  start_node->F = start_node->G + start_node->H;

  open.clear();
  closed.clear();
  open.push_back(start_node);
}

bool AStar::step(const Structures::GraphPtr &graph, const Structures::GraphNodePtr &start, const Structures::GraphNodePtr &goal, std::vector<Structures::GraphEdgePtr> &path)
{
  steps++;
  AStarNodePtr x = open.front(); open.pop_front();
  if(x->node->getUID() == goal->getUID())
  {
    goal_node = x;
    return true;
  }

  const std::vector<GraphEdgePtr> &edges = x->node->getAdjNodes();
  std::for_each(begin(edges), end(edges), [&](const GraphEdgePtr &edge)
  {
    AStarNodePtr y = std::make_shared<AStarNode>();
    y->node = edge->getTo();
    float y_new_G = x->G + (float)edge->getCost();

    auto open_it = open.begin();
    for(; open_it != open.end(); ++open_it)
    {
      if((*open_it)->node->getUID() == y->node->getUID())
        break;
    }
    if(open_it != open.end())
    {
      if((*open_it)->G <= y_new_G)
        return;
    }

    auto closed_it = closed.begin();
    for(; closed_it != closed.end(); ++closed_it)
    {
      if((*closed_it)->node->getUID() == y->node->getUID())
        break;
    }
    if(closed_it != closed.end())
    {
      if((*closed_it)->G <= y_new_G)
        return;
    }

	y->node->setParent(x->node);
    y->G = y_new_G;
    y->H = goalDistanceEstimate(graph, y->node, goal);
    y->F = y->G + y->H;

    if(closed_it != closed.end())
      closed.erase(closed_it);

    if(open_it != open.end())
      open.erase(open_it);

    y->node->setVisitStatus(GraphNode::VISITED);
    open.push_back(y);
  });

  x->node->setVisitStatus(GraphNode::VISITED);
  closed.push_back(x);

  return false;
}

float AStar::goalDistanceEstimate(const Structures::GraphPtr &graph, const Structures::GraphNodePtr &start, const Structures::GraphNodePtr &goal)
{
	//Finish this...
	irr::core::vector3df start_pos = start->get<irr::core::vector3df>("Position").get();
	irr::core::vector3df goal_pos = goal->get<irr::core::vector3df>("Position").get();

	irr::core::vector2df start_pos2D = irr::core::vector2df(start_pos.X, start_pos.Z);
	irr::core::vector2df goal_pos2D = irr::core::vector2df(goal_pos.X, goal_pos.Z);

  return start_pos2D.getDistanceFrom(goal_pos2D);
}

void AStar::constructPath(const Structures::GraphNodePtr &node, std::vector<Structures::GraphEdgePtr> &path)
{
  //Check parent from goal_node to start_node...
	if(node->getParent() == nullptr)
		return;

	//Find reverse order edge
	GraphEdgePtr edge = node->getParent()->getAdjNode(node);
	if(edge == nullptr)
		return;

	constructPath(node->getParent(), path);
	path.push_back(edge);
}

bool AStar::sort(const Structures::GraphNodePtr &x, const Structures::GraphNodePtr &y)
{
  return (x->get<float>("F").get() > y->get<float>("F").get());
}


