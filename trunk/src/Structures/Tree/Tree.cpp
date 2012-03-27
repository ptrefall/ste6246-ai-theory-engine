#include "Tree.h"
#include "TreeNode.h"
#include <algorithm>

using namespace Structures;

Tree::Tree()
  : uid(0)
{
}

Tree::~Tree()
{
  std::for_each(begin(nodes), end(nodes), [](const TreeNodePtr &node)
  {
    node->clearParentNode();
    node->clearChildNodes();
  });
}

void Tree::clearVisited()
{
  std::for_each(begin(nodes), end(nodes), [](const TreeNodePtr &node)
  {
    node->clearVisited();
  });
}

const TreeNodePtr &Tree::addNode(const TreeNodePtr &node)
{
  node->setUID(uid++);
  nodes.push_back(node);
  return node;
}

