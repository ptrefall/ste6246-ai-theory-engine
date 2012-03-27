#include "GraphNode.h"

#include "GraphEdge.h"

using namespace Structures;

GraphNode::GraphNode()
  : visit_status(NOT_VISITED)
{
}

GraphNode::~GraphNode()
{
}

void GraphNode::clearAdjNodes()
{
  adj_nodes.clear();
}

void GraphNode::clearVisited()
{
  visit_status = NOT_VISITED;
}

GraphEdgePtr GraphNode::addAdjNode(const GraphNodePtr &node, unsigned int cost)
{
  GraphEdgePtr edge = std::make_shared<GraphEdge>(shared_from_this(), node, cost);
  adj_nodes.push_back(edge);
  return edge;
}

