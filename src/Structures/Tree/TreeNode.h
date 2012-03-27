#pragma once

#include <Totem\PropertyContainer.h>

#include <memory>
#include <vector>

namespace Structures
{
  class TreeEdge;
  typedef std::shared_ptr<TreeEdge> TreeEdgePtr;

  class TreeNode;
  typedef std::shared_ptr<TreeNode> TreeNodePtr;

  class TreeNode :  public Totem::PropertyContainer<>, public std::enable_shared_from_this<TreeNode>
  {
  public:
    TreeNode();
    virtual ~TreeNode();

    void setUID(unsigned int uid) { this->uid = uid; }
    unsigned int getUID() const { return uid; }

    void clearParentNode();
    void clearChildNodes();
    void clearVisited();

  public:
    enum VisitStatus {
      NOT_VISITED = 0,
      VISITED
    };

    VisitStatus getVisitStatus() const { return visit_status; }
    void setVisitStatus(VisitStatus visit_status) { this->visit_status = visit_status; }

  public:
    TreeEdgePtr setParentNode(const TreeNodePtr &node, unsigned int cost);
    const TreeEdgePtr &getParentNode() const { return parent_node; }

  public:
    TreeEdgePtr addChildNode(const TreeNodePtr &node, unsigned int cost);
    std::vector<TreeEdgePtr> &getChildNodes() { return child_nodes; }
    const std::vector<TreeEdgePtr> &getChildNodes() const { return child_nodes; }

  private:
    unsigned int uid;
    TreeEdgePtr parent_node;
    std::vector<TreeEdgePtr> child_nodes;
    VisitStatus visit_status;
  };
}
