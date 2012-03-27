#pragma once

#include <Totem\PropertyContainer.h>

#include <memory>

namespace Structures
{
  class TreeNode;
  typedef std::shared_ptr<TreeNode> TreeNodePtr;

  class TreeEdge;
  typedef std::shared_ptr<TreeEdge> TreeEdgePtr;

  class TreeEdge : public Totem::PropertyContainer<>
  {
  public:
    TreeEdge(const TreeNodePtr &parent, const TreeNodePtr &child, unsigned int cost = 0);
    ~TreeEdge();

    const TreeNodePtr &getParent() const { return parent; }
    const TreeNodePtr &getChild() const { return child; }
    unsigned int getCost() const { return cost; }

  public:
    TreeNodePtr parent;
    TreeNodePtr child;
    unsigned int cost;
  };
}
