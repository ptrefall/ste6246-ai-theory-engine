#include "GraphNode.h"

#include "GraphEdge.h"

using namespace Structures;

GraphNode::GraphNode()
  : parent(nullptr), visit_status(NOT_VISITED)
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

GraphEdgePtr GraphNode::addAdjNode(const GraphNodePtr &node, float cost)
{
  GraphEdgePtr edge = std::make_shared<GraphEdge>(shared_from_this(), node, cost);
  adj_nodes.push_back(edge);
  return edge;
}

GraphEdgePtr GraphNode::getAdjNode(const GraphNodePtr &node)
{
	for(auto i = 0; i < adj_nodes.size(); i++)
	{
		if(adj_nodes[i]->getTo()->getUID() == node->getUID())
			return adj_nodes[i];
	}
	return nullptr;
}
