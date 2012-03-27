#include "TreeNode.h"

#include "TreeEdge.h"

using namespace Structures;

TreeNode::TreeNode()
  : visit_status(NOT_VISITED)
{
}

TreeNode::~TreeNode()
{
}

void TreeNode::clearParentNode()
{
  parent_node.reset();
}

void TreeNode::clearChildNodes()
{
  child_nodes.clear();
}

void TreeNode::clearVisited()
{
  visit_status = NOT_VISITED;
}

TreeEdgePtr TreeNode::setParentNode(const TreeNodePtr &node, unsigned int cost)
{
  parent_node = std::make_shared<TreeEdge>(node, shared_from_this(), cost);
  return parent_node;
}

TreeEdgePtr TreeNode::addChildNode(const TreeNodePtr &node, unsigned int cost)
{
  TreeEdgePtr edge = std::make_shared<TreeEdge>(shared_from_this(), node, cost);
  child_nodes.push_back(edge);
  return edge;
}

