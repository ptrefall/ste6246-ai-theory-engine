#include "DepthFirst.h"

#include <algorithm>

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
      }
    });
  }

  return false;
}
