#include "DepthFirst.h"

#include <algorithm>
#include <iostream>

using namespace Algorithms;
using namespace Search;

using namespace Structures;

DepthFirst::DepthFirst()
{
}

DepthFirst::~DepthFirst()
{
}

std::vector<TreeEdgePtr> DepthFirst::search(const TreePtr &tree, const TreeNodePtr &start, const TreeNodePtr &goal)
{
  std::vector<TreeEdgePtr> path;
  std::list<TreeNodePtr> queue;
  visit(queue, start, goal, path);
  tree->clearVisited();
  return path;
}

bool DepthFirst::visit(std::list<TreeNodePtr> &queue, const TreeNodePtr &node, const Structures::TreeNodePtr &goal, std::vector<TreeEdgePtr> &path)
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
          queue.push_front(y);
          path.push_back(edge);
          y->setVisitStatus(TreeNode::VISITED);
      }
    });
  }

  return false;
}

std::vector<GraphEdgePtr> DepthFirst::search(const GraphPtr &graph, const GraphNodePtr &start, const GraphNodePtr &goal)
{
  std::vector<GraphEdgePtr> path;
  std::list<GraphNodePtr> queue;
  bool success = visit(queue, start, goal, path);
  std::cout << ((success == true) ? "Found the path!" : "Failed to find the path!") << " " << path.size() << " path-edges generated on a graph of " << graph->getNodes().size() << " nodes!" << std::endl;
  graph->clearVisited();
  return path;
}

bool DepthFirst::visit(std::list<GraphNodePtr> &queue, const GraphNodePtr &node, const Structures::GraphNodePtr &goal, std::vector<GraphEdgePtr> &path)
{
  queue.push_back(node);
  while(!queue.empty())
  {
    GraphNodePtr x = queue.front(); queue.pop_front();
    if(x->getUID() == goal->getUID())
      return true;

    const std::vector<GraphEdgePtr> &edges = x->getAdjNodes();
    std::for_each(begin(edges), end(edges), [&](const GraphEdgePtr &edge)
    {
      GraphNodePtr y = edge->getTo();
      if(y->getVisitStatus() == GraphNode::NOT_VISITED)
      {
          queue.push_front(y);
          path.push_back(edge);
          y->setVisitStatus(GraphNode::VISITED);
      }
    });
  }

  return false;
}
