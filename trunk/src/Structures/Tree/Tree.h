#pragma once

#include <memory>
#include <vector>

namespace Structures
{
  class TreeNode;
  typedef std::shared_ptr<TreeNode> TreeNodePtr;

  class Tree;
  typedef std::shared_ptr<Tree> TreePtr;

  class Tree
  {
  public:
    Tree();
    ~Tree();

  public:
    void clearVisited();

  public:
    const TreeNodePtr &addNode(const TreeNodePtr &node);
    std::vector<TreeNodePtr> &getNodes() { return nodes; }
    const std::vector<TreeNodePtr> &getNodes() const { return nodes; }

  private:
    std::vector<TreeNodePtr> nodes;
    unsigned int uid;
  };
}
