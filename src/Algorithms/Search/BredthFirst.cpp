#include "BredthFirst.h"

#include <algorithm>

using namespace Algorithms;
using namespace Search;

using namespace Structures;

BredthFirst::BredthFirst()
{
}

BredthFirst::~BredthFirst()
{
}

std::vector<TreeEdgePtr> BredthFirst::search(const TreePtr &tree, const TreeNodePtr &start, const TreeNodePtr &goal)
{
  std::vector<TreeEdgePtr> path;
  std::list<TreeNodePtr> queue;
  visit(queue, start, goal, path);
  tree->clearVisited();
  return path;
}

bool BredthFirst::visit(std::list<TreeNodePtr> &queue, const TreeNodePtr &node, const Structures::TreeNodePtr &goal, std::vector<TreeEdgePtr> &path)
{
  queue.push_back(node);
  while(!queue.empty())
  {
    TreeNodePtr x = queue.front(); queue.pop_front();
    if(x->getUID() == goal->getUID())
      return true;

    const std::vector<TreeEdgePtr> &edges = x->getChildNodes();
    std::for_each(begin(edges), end(edges), [&](const TreeEdgePtr &edge)
    {
      TreeNodePtr y = edge->getChild();
      if(y->getVisitStatus() == TreeNode::NOT_VISITED)
      {
          queue.push_back(y);
          path.push_back(edge);
      }
    });
  }

  return false;
}

std::vector<GraphEdgePtr> BredthFirst::search(const GraphPtr &graph, const GraphNodePtr &start, const GraphNodePtr &goal)
{
  std::vector<GraphEdgePtr> path;
  std::list<GraphNodePtr> queue;
  visit(queue, start, goal, path);
  graph->clearVisited();
  return path;
}

bool BredthFirst::visit(std::list<GraphNodePtr> &queue, const GraphNodePtr &node, const Structures::GraphNodePtr &goal, std::vector<GraphEdgePtr> &path)
{
  queue.push_back(node);
  while(!queue.empty())
  {
    GraphNodePtr x = queue.front(); queue.pop_front();
    if(x->getUID() == goal->getUID())
      return true;

    x->setVisitStatus(GraphNode::VISITED);

    const std::vector<GraphEdgePtr> &edges = x->getAdjNodes();
    std::for_each(begin(edges), end(edges), [&](const GraphEdgePtr &edge)
    {
      GraphNodePtr y = edge->getTo();
      if(y->getVisitStatus() == GraphNode::NOT_VISITED)
      {
          y->setVisitStatus(GraphNode::VISITED);
          queue.push_back(y);
          path.push_back(edge);
      }
    });
  }

  return false;
}
